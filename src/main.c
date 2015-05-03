#include <pebble.h>
#include <catch.h>
 
Window* window;
TextLayer *time_layer;
TextLayer *latitude_layer;
char time_buffer[64]; char latitude_buffer[64];
enum {
  KEY_LATITUDE = 1,
};

TextLayer *poke_layer;
char poke_buffer[64];


// Add-on
static catch_t catch_obj;

static void in_received_handler(DictionaryIterator *iter, void *context)
{
  //How to process received Tuples.
  (void) context;
     
    //Get data
    //Read first item
    Tuple *t = dict_read_first(iter);
    //Repeat reading until no more returned
    while(t != NULL)
    {
        // switch based process_tuple() fn to spearate out the process
        int key = t->key;
        int value = t->value->int32;
        catch_obj.lati = value;
        switch(key) {
        case KEY_LATITUDE:
          snprintf(latitude_buffer, sizeof("Latitude: XX"), "Latitude: %d", value);
          text_layer_set_text(latitude_layer, (char*) &latitude_buffer);
          break;
        }
        t = dict_read_next(iter);
    }
}
// callback for receiving data from phone

// 4/17 Kim's Code:
void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
      catch_timer(&catch_obj, time_layer);
      catch_decide(&catch_obj, poke_layer);
}

static void click_config_provider(void *context) {
  // 4/17 Kim's Code:
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static TextLayer* init_text_layer(GRect location, GColor colour, GColor background, const char *res_id, GTextAlignment alignment)
{
  TextLayer *layer = text_layer_create(location);
  text_layer_set_text_color(layer, colour);
  text_layer_set_background_color(layer, background);
  text_layer_set_font(layer, fonts_get_system_font(res_id));
  text_layer_set_text_alignment(layer, alignment);
 
  return layer;
}

void window_load(Window *window)
{ 
  latitude_layer = init_text_layer(GRect(5, 60, 144, 30), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
  text_layer_set_text(latitude_layer, "Latitude: N/A");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(latitude_layer));
  
  time_layer = init_text_layer(GRect(35, 90, 144, 30), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
  
  time_layer = init_text_layer(GRect(55, 160, 144, 30), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(poke_layer));
}
 
void window_unload(Window *window)
{
  text_layer_destroy(latitude_layer);
  text_layer_destroy(time_layer);
  text_layer_destroy(poke_layer);
}

void init()
{
  window = window_create();
  WindowHandlers handlers = {
    .load = window_load,
    .unload = window_unload
  };
  window_set_window_handlers(window, handlers);
  
  window_set_click_config_provider(window, click_config_provider);
  
  //Set up appmessage itself
  app_message_register_inbox_received(in_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());    //Largest possible input and output buffer sizes
 
  window_stack_push(window, true);
}
 
void deinit()
{
  // corresponding de-init procedure.
  window_destroy(window);
}
 
int main(void)
{
  init();
  app_event_loop();
  deinit();
}