#include "Configuration.h"
#include "UltiLCD2.h"
#include "UltiLCD2_hi_lib.h"
#include "UltiLCD2_gfx.h"
#include "UltiLCD2_menu_maintenance.h"
#include "UltiLCD2_menu_first_run.h"
#include "UltiLCD2_menu_material.h"
#include "cardreader.h"
#include "lifetime_stats.h"
#include "ConfigurationStore.h"
#include "temperature.h"
#include "pins.h"
#include "Marlin.h"
#include "UltiLCD2_hi_lib.h"
#include "UltiLCD2_menu_print.h"

void lcd_advanced_type();
void lcd_advanced_type_tune();
void brim_menu();
void first_menu();
void support_menu();
void interface_top_menu();
void bottom_menu();
void inner_wall_menu();
void outer_wall_menu();
void infill_menu();
void top_menu();
void interface_bot_menu();
void travel_menu();
void quality_menu();

bool tune_type = false;

static char* lcd_type_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Brim"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("First Layer"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Support"));
    else if (nr == 4)
        strcpy_P(card.longFilename, PSTR("Interface Roof"));
    else if (nr == 5)
        strcpy_P(card.longFilename, PSTR("Bottom"));
    else if (nr == 6)
        strcpy_P(card.longFilename, PSTR("Outer Wall"));
    else if (nr == 7)
        strcpy_P(card.longFilename, PSTR("Inner Wall"));
    else if (nr == 8)
        strcpy_P(card.longFilename, PSTR("Infill"));
    else if (nr == 9)
        strcpy_P(card.longFilename, PSTR("Top"));
    else if (nr == 10)
        strcpy_P(card.longFilename, PSTR("Interface Floor"));
    else if (nr == 11)
        strcpy_P(card.longFilename, PSTR("Travel"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_type_details(uint8_t nr)
{
    /*
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
        return;
    else if(nr == 2)
        return;
    else if(nr == 3)
        return;
    else if(nr == 4)
        return;
    else if(nr == 5)
        return;
    else if(nr == 6)
        return;
    else if(nr == 7)
        return;
    else if(nr == 8)
        return;  
    else if(nr == 9)
        return;
    else if(nr == 10)
        return;
    else if(nr == 11)
        return;
    lcd_lib_draw_string(5, 53, buffer);
    */
}


static void lcd_advanced_type()
{
    lcd_scroll_menu(PSTR("Type Settings"), 12, lcd_type_item, lcd_type_details);
    if (lcd_lib_button_pressed)
    {
        tune_type = false;
        
        if (IS_SELECTED_SCROLL(0))
        {
            Config_StoreSettings();
            lcd_change_to_menu(lcd_menu_maintenance_advanced, 0);
        }
        else if (IS_SELECTED_SCROLL(1))
            lcd_change_to_menu(brim_menu, 0);
        else if (IS_SELECTED_SCROLL(2))
            lcd_change_to_menu(first_menu, 0);
        else if (IS_SELECTED_SCROLL(3))
            lcd_change_to_menu(support_menu, 0);
        else if (IS_SELECTED_SCROLL(4))
            lcd_change_to_menu(interface_top_menu, 0);
        else if (IS_SELECTED_SCROLL(5))
            lcd_change_to_menu(bottom_menu, 0);
        else if (IS_SELECTED_SCROLL(6))
            lcd_change_to_menu(outer_wall_menu, 0);
        else if (IS_SELECTED_SCROLL(7))
            lcd_change_to_menu(inner_wall_menu, 0);
        else if (IS_SELECTED_SCROLL(8))
            lcd_change_to_menu(infill_menu, 0);
        else if (IS_SELECTED_SCROLL(9))
            lcd_change_to_menu(top_menu, 0);
        else if (IS_SELECTED_SCROLL(10))
            lcd_change_to_menu(interface_bot_menu, 0);
        else if (IS_SELECTED_SCROLL(11))
            lcd_change_to_menu(travel_menu, 0);

    }
}

static void lcd_advanced_type_tune()
{
    lcd_scroll_menu(PSTR("Type Settings"), 12, lcd_type_item, lcd_type_details);
    if (lcd_lib_button_pressed)
    {
        tune_type = true;
        if (IS_SELECTED_SCROLL(0))
        {
            Config_StoreSettings();
            lcd_change_to_menu(lcd_menu_print_tune, 0);
        }
        else if (IS_SELECTED_SCROLL(1))
            lcd_change_to_menu(brim_menu, 0);
        else if (IS_SELECTED_SCROLL(2))
            lcd_change_to_menu(first_menu, 0);
        else if (IS_SELECTED_SCROLL(3))
            lcd_change_to_menu(support_menu, 0);
        else if (IS_SELECTED_SCROLL(4))
            lcd_change_to_menu(interface_top_menu, 0);
        else if (IS_SELECTED_SCROLL(5))
            lcd_change_to_menu(bottom_menu, 0);
        else if (IS_SELECTED_SCROLL(6))
            lcd_change_to_menu(outer_wall_menu, 0);
        else if (IS_SELECTED_SCROLL(7))
            lcd_change_to_menu(inner_wall_menu, 0);
        else if (IS_SELECTED_SCROLL(8))
            lcd_change_to_menu(infill_menu, 0);
        else if (IS_SELECTED_SCROLL(9))
            lcd_change_to_menu(top_menu, 0);
        else if (IS_SELECTED_SCROLL(10))
            lcd_change_to_menu(interface_bot_menu, 0);
        else if (IS_SELECTED_SCROLL(11))
            lcd_change_to_menu(travel_menu, 0);

    }
}

///////////////////////////brim////////////////////////////////////

static char* lcd_brim_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_brim_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(brim_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(brim_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(brim_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(brim_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(brim_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(brim_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(brim_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(brim_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(brim_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void brim_menu()
{
    lcd_scroll_menu(PSTR("Skirt/Brim Settings"), 4, lcd_brim_item, lcd_brim_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(brim_feed_d, "Skirt/Brim Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(brim_feed_n, "Skirt/Brim Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(brim_feed_b, "Skirt/Brim Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(brim_flow_d, "Skirt/Brim Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(brim_flow_n, "Skirt/Brim Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(brim_flow_b, "Skirt/Brim Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(brim_fan_d, "Skirt/Brim Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(brim_fan_n, "Skirt/Brim Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(first_fan_b, "Skirt/Brim Fanspeed", "%", 0, 100);
        }
    }
}

///////////////////////first layer////////////////////////////

static char* lcd_first_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_first_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(first_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(first_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(first_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(first_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(first_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(first_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(first_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(first_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(first_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void first_menu()
{
    lcd_scroll_menu(PSTR("First Layer Settings"), 4, lcd_first_item, lcd_first_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(first_feed_d, "First Layer Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(first_feed_n, "First Layer Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(first_feed_b, "First Layer Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(first_flow_d, "First Layer Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(first_flow_n, "First Layer Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(first_flow_b, "First Layer Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(first_fan_d, "First Layer Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(first_fan_n, "First Layer Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(first_fan_b, "First Layer Fanspeed", "%", 0, 100);
        }
    }
}


//////////////////////support/////////////////////////////

static char* lcd_support_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_support_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(support_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(support_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(support_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(support_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(support_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(support_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(support_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(support_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(support_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void support_menu()
{
    lcd_scroll_menu(PSTR("Support Settings"), 4, lcd_support_item, lcd_support_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(support_feed_d, "Support Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(support_feed_n, "Support Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(support_feed_b, "Support Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(support_flow_d, "Support Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(support_flow_n, "Support Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(support_flow_b, "Support Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(support_fan_d, "Support Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(support_fan_n, "Support Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(support_fan_b, "Support Fanspeed", "%", 0, 100);
        }
    }
}


//////////////////////interface roof/////////////////////////////

static char* lcd_interface_top_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_interface_top_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacetop_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacetop_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacetop_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacetop_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacetop_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacetop_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacetop_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacetop_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacetop_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void interface_top_menu()
{
    lcd_scroll_menu(PSTR("Interface Roof"), 4, lcd_interface_top_item, lcd_interface_top_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(interfacetop_feed_d, "Interface Roof Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(interfacetop_feed_n, "Interface Roof Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(interfacetop_feed_b, "Interface Roof Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(interfacetop_flow_d, "Interface Roof Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(interfacetop_flow_n, "Interface Roof Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(interfacetop_flow_b, "Interface Roof Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(interfacetop_fan_d, "Interface Roof Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(interfacetop_fan_n, "Interface Roof Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(interfacetop_fan_b, "Interface Roof Fanspeed", "%", 0, 100);
        }
    }
}


//////////////////////bottom/////////////////////////////

static char* lcd_bottom_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_bottom_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(bottom_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(bottom_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(bottom_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(bottom_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(bottom_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(bottom_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(bottom_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(bottom_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(bottom_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void bottom_menu()
{
    lcd_scroll_menu(PSTR("Bottom Settings"), 4, lcd_bottom_item, lcd_bottom_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(bottom_feed_d, "Bottom Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(bottom_feed_n, "Bottom Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(bottom_feed_b, "Bottom Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(bottom_flow_d, "Bottom Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(bottom_flow_n, "Bottom Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(bottom_flow_b, "Bottom Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(bottom_fan_d, "Bottom Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(bottom_fan_n, "Bottom Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(bottom_fan_b, "Bottom Fanspeed", "%", 0, 100);
        }
    }
}


//////////////////////outer wall/////////////////////////////

static char* lcd_outer_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_outer_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(outer_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(outer_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(outer_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(outer_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(outer_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(outer_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(outer_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(outer_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(outer_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void outer_wall_menu()
{
    lcd_scroll_menu(PSTR("Outer Settings"), 4, lcd_outer_item, lcd_outer_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(outer_feed_d, "Outer Wall Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(outer_feed_n, "Outer Wall Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(outer_feed_b, "Outer Wall Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(outer_flow_d, "Outer Wall Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(outer_flow_n, "Outer Wall Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(outer_flow_b, "Outer Wall Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(outer_fan_d, "Outer Wall Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(outer_fan_n, "Outer Wall Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(outer_fan_b, "Outer Wall Fanspeed", "%", 0, 100);
        }
    }
}

//////////////////////inner wall/////////////////////////////

static char* lcd_inner_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_inner_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(inner_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(inner_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(inner_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(inner_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(inner_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(inner_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(inner_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(inner_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(inner_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void inner_wall_menu()
{
    lcd_scroll_menu(PSTR("Inner Settings"), 4, lcd_inner_item, lcd_inner_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(inner_feed_d, "Inner Wall Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(inner_feed_n, "Inner Wall Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(inner_feed_b, "Inner Wall Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(inner_flow_d, "Inner Wall Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(inner_flow_n, "Inner Wall Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(inner_flow_b, "Inner Wall Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(inner_fan_d, "Inner Wall Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(inner_fan_n, "Inner Wall Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(inner_fan_b, "Inner Wall Fanspeed", "%", 0, 100);
        }
    }
}


//////////////////////Infill////////////////////////////

static char* lcd_infill_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_infill_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(infill_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(infill_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(infill_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(infill_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(infill_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(infill_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(infill_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(infill_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(infill_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void infill_menu()
{
    lcd_scroll_menu(PSTR("Infill Settings"), 4, lcd_infill_item, lcd_infill_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(infill_feed_d, "Infill Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(infill_feed_n, "Infill Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(infill_feed_b, "Infill Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(infill_flow_d, "Infill Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(infill_flow_n, "Infill Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(infill_flow_b, "Infill Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(infill_fan_d, "Infill Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(infill_fan_n, "Infill Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(infill_fan_b, "Infill Fanspeed", "%", 0, 100);
        }
    }
}

//////////////////////Top////////////////////////////
static char* lcd_top_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_top_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(top_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(top_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(top_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(top_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(top_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(top_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(top_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(top_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(top_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void top_menu()
{
    lcd_scroll_menu(PSTR("Top Settings"), 4, lcd_top_item, lcd_top_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(top_feed_d, "Top Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(top_feed_n, "Top Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(top_feed_b, "Top Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(top_flow_d, "Top Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(top_flow_n, "Top Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(top_flow_b, "Top Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(top_fan_d, "Top Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(top_fan_n, "Top Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(top_fan_b, "Top Fanspeed", "%", 0, 100);
        }
    }
}

//////////////////////interface floor////////////////////////////

static char* lcd_interfacebot_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_interfacebot_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacebot_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacebot_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacebot_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacebot_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacebot_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacebot_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacebot_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacebot_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacebot_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void interface_bot_menu()
{
    lcd_scroll_menu(PSTR("Interface Floor"), 4, lcd_interfacebot_item, lcd_interfacebot_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(interfacebot_feed_d, "Interface Floor Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(interfacebot_feed_n, "Interface Floor Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(interfacebot_feed_b, "Interface Floor Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(interfacebot_flow_d, "Interface Floor Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(interfacebot_flow_n, "Interface Floor Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(interfacebot_flow_b, "Interface Floor Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(interfacebot_fan_d, "Interface Floor Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(interfacebot_fan_n, "Interface Floor Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(interfacebot_fan_b, "Interface Floor Fanspeed", "%", 0, 100);
        }
    }
}

//////////////////////travel////////////////////////////

static char* lcd_travel_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Fan"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_travel_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(travel_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(travel_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(travel_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(travel_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(travel_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(travel_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(travel_fan_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(travel_fan_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(travel_fan_b, buffer, PSTR("%"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void travel_menu()
{
    lcd_scroll_menu(PSTR("Travel Settings"), 4, lcd_travel_item, lcd_travel_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_d, "Travel Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_n, "Travel Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_b, "Travel Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(travel_flow_d, "Travel Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(travel_flow_n, "Travel Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(travel_flow_b, "Travel Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(travel_fan_d, "Travel Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(travel_fan_n, "Travel Fanspeed", "%", 0, 100);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(travel_fan_b, "Travel Fanspeed", "%", 0, 100);
        }
    }
}

///////////////quality//////////////////////

static char* lcd_quality_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR(" Draft"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR(" Normal"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR(" Best"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    if (nr - 1 == print_quality)
        card.longFilename[0] = '>';
    return card.longFilename;
}

static void lcd_quality_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
        return;
    else if(nr == 2)
        return;
    else if(nr == 3)
        return;
    lcd_lib_draw_string(5, 53, buffer);
}

static void quality_menu()
{
    lcd_scroll_menu(PSTR("Print Quality"), 4, lcd_quality_item, lcd_quality_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                Config_StoreSettings();
                lcd_lib_beep();
                lcd_change_to_menu(previousMenu, 0);
            }
            else
            {
                Config_StoreSettings();
                lcd_lib_beep();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            print_quality = PRINT_QUALITY_DRAFT;
            Config_StoreSettings();
            lcd_lib_beep();
            lcd_change_to_menu(lcd_menu_print_printing);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            print_quality = PRINT_QUALITY_NORMAL;
            Config_StoreSettings();
            lcd_lib_beep();
            lcd_change_to_menu(lcd_menu_print_printing);
        }

        else if (IS_SELECTED_SCROLL(3))        
        {
            print_quality = PRINT_QUALITY_BEST;
            Config_StoreSettings();
            lcd_lib_beep();
            lcd_change_to_menu(lcd_menu_print_printing);
        }
    }

}
