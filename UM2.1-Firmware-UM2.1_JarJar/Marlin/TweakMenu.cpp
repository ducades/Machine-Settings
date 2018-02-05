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
void retract_menu();

void quality_menu();
void lcd_menu_header_select();
void set_header_true();
void set_header_false();

void set_brim_true();
void set_brim_false();
void set_first_true();
void set_first_false();
void set_support_true();
void set_support_false();
void set_roof_true();
void set_roof_false();
void set_bottom_true();
void set_bottom_false();
void set_outer_true();
void set_outer_false();
void set_inner_true();
void set_inner_false();
void set_infill_true();
void set_infill_false();
void set_top_true();
void set_top_false();
void set_floor_true();
void set_floor_false();
void set_travel_true();
void set_travel_false();

void use_brim();
void use_first();
void use_support();
void use_roof();
void use_bottom();
void use_outer();
void use_inner();
void use_infill();
void use_top();
void use_floor();
void use_travel();
void use_retract();



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
    else if (nr == 12)
        strcpy_P(card.longFilename, PSTR("Retract"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_type_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;
    else if(nr == 1)
     {
        if (BRIM == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 2)
    {
        if (FIRST == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 3)
    {
        if (SUPPORT == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 4)
    {
        if (ROOF == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 5)
    {
        if (BOTTOM == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 6)
    {
        if (OUTER == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 7)
    {
        if (INNER == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 8)
    {
        if (INFILL == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    } 
    else if(nr == 9)
    {
        if (TOP == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 10)
    {
        if (FLOOR == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 11)
    {
        if (TRAVEL == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 12)
    {
        if (RETRACT == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    lcd_lib_draw_string(5, 53, buffer);
}


static void lcd_advanced_type()
{
    lcd_scroll_menu(PSTR("Type Settings"), 13, lcd_type_item, lcd_type_details);
    if (lcd_lib_button_pressed)
    {
        tune_type = false;
        
        if (IS_SELECTED_SCROLL(0))
        {
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
        else if (IS_SELECTED_SCROLL(12))
            lcd_change_to_menu(retract_menu, 0);

    }
}

static void lcd_advanced_type_tune()
{
    lcd_scroll_menu(PSTR("Type Settings"), 13, lcd_type_item, lcd_type_details);
    if (lcd_lib_button_pressed)
    {
        tune_type = true;
        if (IS_SELECTED_SCROLL(0))
        {
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
        else if (IS_SELECTED_SCROLL(12))
            lcd_change_to_menu(retract_menu, 0);

    }
}

///////////////////////////brim////////////////////////////////////

static char* lcd_brim_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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
    else if (nr == 1)
    {
        if (BRIM == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(brim_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(brim_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(brim_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(brim_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(brim_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(brim_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(brim_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(brim_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(brim_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void brim_menu()
{
    lcd_scroll_menu(PSTR("Skirt/Brim Settings"), 5, lcd_brim_item, lcd_brim_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_brim, 0);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(brim_feed_d, "Skirt/Brim Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(brim_feed_n, "Skirt/Brim Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(brim_feed_b, "Skirt/Brim Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(brim_flow_d, "Skirt/Brim Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(brim_flow_n, "Skirt/Brim Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(brim_flow_b, "Skirt/Brim Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(brim_fan_d, "Skirt/Brim Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(brim_fan_n, "Skirt/Brim Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(first_fan_b, "Skirt/Brim Fanspeed", " PWM", 0, 255);
        }
    }
}

///////////////////////first layer////////////////////////////

static char* lcd_first_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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

    else if (nr == 1)
    {
        if (FIRST == true)
            strcpy_P(buffer, PSTR("Yes"));

        else
            strcpy_P(buffer, PSTR("No"));

    }
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(first_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(first_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(first_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(first_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(first_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(first_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(first_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(first_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(first_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void first_menu()
{
    lcd_scroll_menu(PSTR("First Layer Settings"), 5, lcd_first_item, lcd_first_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_first, 0);
        }
        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(first_feed_d, "First Layer Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(first_feed_n, "First Layer Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(first_feed_b, "First Layer Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(first_flow_d, "First Layer Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(first_flow_n, "First Layer Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(first_flow_b, "First Layer Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(first_fan_d, "First Layer Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(first_fan_n, "First Layer Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(first_fan_b, "First Layer Fanspeed", " PWM", 0, 255);
        }
    }
}


//////////////////////support/////////////////////////////

static char* lcd_support_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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
   
    else if (nr == 1)
    {
        if (SUPPORT == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(support_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(support_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(support_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(support_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(support_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(support_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(support_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(support_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(support_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void support_menu()
{
    lcd_scroll_menu(PSTR("Support Settings"), 5, lcd_support_item, lcd_support_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_support, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(support_feed_d, "Support Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(support_feed_n, "Support Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(support_feed_b, "Support Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(support_flow_d, "Support Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(support_flow_n, "Support Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(support_flow_b, "Support Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(support_fan_d, "Support Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(support_fan_n, "Support Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(support_fan_b, "Support Fanspeed", " PWM", 0, 255);
        }
    }
}


//////////////////////interface roof/////////////////////////////

static char* lcd_interface_top_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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
    
    else if (nr == 1)
    {
        if (ROOF == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }
    
    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacetop_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacetop_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacetop_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacetop_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacetop_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacetop_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacetop_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacetop_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacetop_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void interface_top_menu()
{
    lcd_scroll_menu(PSTR("Interface Roof"), 5, lcd_interface_top_item, lcd_interface_top_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_roof, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(interfacetop_feed_d, "Interface Roof Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(interfacetop_feed_n, "Interface Roof Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(interfacetop_feed_b, "Interface Roof Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(interfacetop_flow_d, "Interface Roof Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(interfacetop_flow_n, "Interface Roof Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(interfacetop_flow_b, "Interface Roof Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(interfacetop_fan_d, "Interface Roof Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(interfacetop_fan_n, "Interface Roof Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(interfacetop_fan_b, "Interface Roof Fanspeed", " PWM", 0, 255);
        }
    }
}


//////////////////////bottom/////////////////////////////

static char* lcd_bottom_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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
   
    else if (nr == 1)
    {
        if (BOTTOM == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(bottom_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(bottom_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(bottom_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(bottom_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(bottom_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(bottom_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(bottom_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(bottom_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(bottom_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void bottom_menu()
{
    lcd_scroll_menu(PSTR("Bottom Settings"), 5, lcd_bottom_item, lcd_bottom_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_bottom, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(bottom_feed_d, "Bottom Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(bottom_feed_n, "Bottom Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(bottom_feed_b, "Bottom Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(bottom_flow_d, "Bottom Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(bottom_flow_n, "Bottom Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(bottom_flow_b, "Bottom Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(bottom_fan_d, "Bottom Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(bottom_fan_n, "Bottom Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(bottom_fan_b, "Bottom Fanspeed", " PWM", 0, 255);
        }
    }
}


//////////////////////outer wall/////////////////////////////

static char* lcd_outer_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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
    
    else if (nr == 1)
    {
        if (OUTER == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(outer_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(outer_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(outer_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(outer_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(outer_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(outer_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(outer_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(outer_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(outer_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void outer_wall_menu()
{
    lcd_scroll_menu(PSTR("Outer Settings"), 5, lcd_outer_item, lcd_outer_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_outer, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(outer_feed_d, "Outer Wall Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(outer_feed_n, "Outer Wall Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(outer_feed_b, "Outer Wall Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(outer_flow_d, "Outer Wall Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(outer_flow_n, "Outer Wall Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(outer_flow_b, "Outer Wall Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(outer_fan_d, "Outer Wall Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(outer_fan_n, "Outer Wall Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(outer_fan_b, "Outer Wall Fanspeed", " PWM", 0, 255);
        }
    }
}

//////////////////////inner wall/////////////////////////////

static char* lcd_inner_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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

    else if (nr == 1)
    {
        if (INNER == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(inner_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(inner_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(inner_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(inner_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(inner_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(inner_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(inner_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(inner_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(inner_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void inner_wall_menu()
{
    lcd_scroll_menu(PSTR("Inner Settings"), 5, lcd_inner_item, lcd_inner_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_inner, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(inner_feed_d, "Inner Wall Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(inner_feed_n, "Inner Wall Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(inner_feed_b, "Inner Wall Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(inner_flow_d, "Inner Wall Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(inner_flow_n, "Inner Wall Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(inner_flow_b, "Inner Wall Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(inner_fan_d, "Inner Wall Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(inner_fan_n, "Inner Wall Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(inner_fan_b, "Inner Wall Fanspeed", " PWM", 0, 255);
        }
    }
}


//////////////////////Infill////////////////////////////

static char* lcd_infill_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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

    else if (nr == 1)
    {
        if (INFILL == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(infill_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(infill_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(infill_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(infill_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(infill_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(infill_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(infill_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(infill_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(infill_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void infill_menu()
{
    lcd_scroll_menu(PSTR("Infill Settings"), 5, lcd_infill_item, lcd_infill_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_infill, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(infill_feed_d, "Infill Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(infill_feed_n, "Infill Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(infill_feed_b, "Infill Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(infill_flow_d, "Infill Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(infill_flow_n, "Infill Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(infill_flow_b, "Infill Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(infill_fan_d, "Infill Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(infill_fan_n, "Infill Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(infill_fan_b, "Infill Fanspeed", " PWM", 0, 255);
        }
    }
}

//////////////////////Top////////////////////////////
static char* lcd_top_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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

    else if (nr == 1)
    {
        if (TOP == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(top_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(top_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(top_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(top_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(top_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(top_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(top_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(top_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(top_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void top_menu()
{
    lcd_scroll_menu(PSTR("Top Settings"), 5, lcd_top_item, lcd_top_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_top, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(top_feed_d, "Top Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(top_feed_n, "Top Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(top_feed_b, "Top Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(top_flow_d, "Top Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(top_flow_n, "Top Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(top_flow_b, "Top Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(top_fan_d, "Top Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(top_fan_n, "Top Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(top_fan_b, "Top Fanspeed", " PWM", 0, 255);
        }
    }
}

//////////////////////interface floor////////////////////////////

static char* lcd_interfacebot_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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
    
    else if (nr == 1)
    {
        if (FLOOR == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacebot_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacebot_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacebot_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacebot_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacebot_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacebot_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(interfacebot_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(interfacebot_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(interfacebot_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void interface_bot_menu()
{
    lcd_scroll_menu(PSTR("Interface Floor"), 5, lcd_interfacebot_item, lcd_interfacebot_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_floor, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(interfacebot_feed_d, "Interface Floor Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(interfacebot_feed_n, "Interface Floor Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(interfacebot_feed_b, "Interface Floor Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(interfacebot_flow_d, "Interface Floor Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(interfacebot_flow_n, "Interface Floor Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(interfacebot_flow_b, "Interface Floor Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(interfacebot_fan_d, "Interface Floor Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(interfacebot_fan_n, "Interface Floor Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(interfacebot_fan_b, "Interface Floor Fanspeed", " PWM", 0, 255);
        }
    }
}

//////////////////////travel////////////////////////////

static char* lcd_travel_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Flow"));
    else if (nr == 4)
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

    else if (nr == 1)
    {
        if (TRAVEL == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(travel_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(travel_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(travel_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(travel_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(travel_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(travel_flow_b, buffer, PSTR("%"));
    }

    else if(nr == 4)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(travel_fan_d, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(travel_fan_n, buffer, PSTR(" PWM"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(travel_fan_b, buffer, PSTR(" PWM"));
    }

    lcd_lib_draw_string(5, 53, buffer);
}

static void travel_menu()
{
    lcd_scroll_menu(PSTR("Travel Settings"), 5, lcd_travel_item, lcd_travel_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_travel, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_d, "Travel Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_n, "Travel Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_b, "Travel Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(travel_flow_d, "Travel Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(travel_flow_n, "Travel Flowrate", "%", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(travel_flow_b, "Travel Flowrate", "%", 0, 200);
        }
        else if (IS_SELECTED_SCROLL(4))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(travel_fan_d, "Travel Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(travel_fan_n, "Travel Fanspeed", " PWM", 0, 255);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(travel_fan_b, "Travel Fanspeed", " PWM", 0, 255);
        }
    }
}

//////////////////////retract////////////////////////////

static char* lcd_retract_item(uint8_t nr)
{
    if (nr == 0)
        strcpy_P(card.longFilename, PSTR("< RETURN"));
    else if (nr == 1)
        strcpy_P(card.longFilename, PSTR("Used?"));
    else if (nr == 2)
        strcpy_P(card.longFilename, PSTR("Feed"));
    else if (nr == 3)
        strcpy_P(card.longFilename, PSTR("Distance"));
    else
        strcpy_P(card.longFilename, PSTR("???"));
    return card.longFilename;
}

static void lcd_retract_details(uint8_t nr)
{
    char buffer[16];
    if (nr == 0)
        return;

    else if (nr == 1)
    {
        if (RETRACT == true)
            strcpy_P(buffer, PSTR("Yes"));
        else
            strcpy_P(buffer, PSTR("No"));
    }

    else if(nr == 2)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(travel_feed_d, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(travel_feed_n, buffer, PSTR("mm/sec"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(travel_feed_b, buffer, PSTR("mm/sec"));
    }
    else if(nr == 3)
    {
        if (print_quality == PRINT_QUALITY_DRAFT)
            int_to_string(travel_flow_d, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_NORMAL)
            int_to_string(travel_flow_n, buffer, PSTR("%"));
        else if (print_quality == PRINT_QUALITY_BEST)
            int_to_string(travel_flow_b, buffer, PSTR("%"));
    }
    lcd_lib_draw_string(5, 53, buffer);
}

static void retract_menu()
{
    lcd_scroll_menu(PSTR("Retract Settings"), 4, lcd_retract_item, lcd_retract_details);
    if (lcd_lib_button_pressed)
    {
        if (IS_SELECTED_SCROLL(0))
        {
            if (tune_type == false)
            {
                lcd_change_to_menu(lcd_advanced_type, 0);
            }
            else
            {
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }

        else if (IS_SELECTED_SCROLL(1))
        {
            lcd_change_to_menu(use_retract, 0);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_d, "Retract Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_n, "Retract Feed", "mm/sec", 0, 20000);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING_FLOAT1(travel_feed_b, "Retract Feed", "mm/sec", 0, 20000);
        }
        else if (IS_SELECTED_SCROLL(3))
        {
            if (print_quality == PRINT_QUALITY_DRAFT)
                LCD_EDIT_SETTING(travel_flow_d, "Retract Distance", "mm", 0, 200);
            else if (print_quality == PRINT_QUALITY_NORMAL)
                LCD_EDIT_SETTING(travel_flow_n, "Retract Distance", "mm", 0, 200);
            else if (print_quality == PRINT_QUALITY_BEST)
                LCD_EDIT_SETTING(travel_flow_b, "Retract Distance", "mm", 0, 200);
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
                lcd_lib_beep();
                lcd_change_to_menu(previousMenu, 0);
            }
            else
            {
                lcd_lib_beep();
                lcd_change_to_menu(lcd_advanced_type_tune, 0);
            }
        }
        else if (IS_SELECTED_SCROLL(1))
        {
            print_quality = PRINT_QUALITY_DRAFT;
            lcd_lib_beep();
            lcd_change_to_menu(lcd_menu_print_heatup);
        }

        else if (IS_SELECTED_SCROLL(2))
        {
            print_quality = PRINT_QUALITY_NORMAL;
            lcd_lib_beep();
            lcd_change_to_menu(lcd_menu_print_heatup);
        }

        else if (IS_SELECTED_SCROLL(3))        
        {
            print_quality = PRINT_QUALITY_BEST;
            lcd_lib_beep();
            lcd_change_to_menu(lcd_menu_print_heatup);
        }
    }

}

static void lcd_menu_header_select()
{
    LED_GLOW();

    lcd_question_screen(quality_menu, set_header_true, PSTR("YES"), quality_menu, set_header_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use header?"));
    lcd_lib_update_screen();

}

static void set_header_true()
{
    header = true;                            
    enquecommand_P(PSTR("G28"));
    enquecommand_P(PSTR("G1 F3000 X5 Y10")); 
}


static void set_header_false()
{
    header = false;
    enquecommand_P(PSTR("G28"));
    enquecommand_P(PSTR("G1 F3000 X5 Y10")); 
}

static void set_brim_false()
{
    BRIM = false;
}

static void set_brim_true()
{
    BRIM = true; 
}

static void set_first_false()
{
    FIRST = false;
}

static void set_first_true()
{
    FIRST = true; 
}

static void set_support_false()
{
    SUPPORT = false;
}

static void set_support_true()
{
    SUPPORT = true; 
}

static void set_roof_false()
{
    ROOF = false;
}

static void set_roof_true()
{
    ROOF = true; 
}

static void set_bottom_false()
{
    BOTTOM = false;
}

static void set_bottom_true()
{
    BOTTOM = true; 
}

static void set_outer_false()
{
    OUTER = false;
}

static void set_outer_true()
{
    OUTER = true; 
}

static void set_inner_false()
{
    INNER = false;
}

static void set_inner_true()
{
    INNER = true; 
}

static void set_infill_false()
{
    INFILL = false;
}

static void set_infill_true()
{
    INFILL = true; 
}

static void set_top_false()
{
    TOP = false;
}

static void set_top_true()
{
    TOP = true; 
}

static void set_floor_false()
{
    FLOOR = false;
}

static void set_floor_true()
{
    FLOOR = true; 
}
static void set_travel_false()
{
    TRAVEL = false;
}

static void set_travel_true()
{
    TRAVEL = true; 
}

static void set_retract_false()
{
    RETRACT = false;
}

static void set_retract_true()
{
    RETRACT = true; 
}

static void use_brim()
{
    lcd_question_screen(lcd_advanced_type_tune, set_brim_true, PSTR("YES"), lcd_advanced_type_tune, set_brim_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Brim?"));
    lcd_lib_update_screen();
}

static void use_first()
{
    lcd_question_screen(lcd_advanced_type_tune, set_first_true, PSTR("YES"), lcd_advanced_type_tune, set_first_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use First?"));
    lcd_lib_update_screen();
}

static void use_support()
{
    lcd_question_screen(lcd_advanced_type_tune, set_support_true, PSTR("YES"), lcd_advanced_type_tune, set_support_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Support?"));
    lcd_lib_update_screen();
}

static void use_roof()
{
    lcd_question_screen(lcd_advanced_type_tune, set_roof_true, PSTR("YES"), lcd_advanced_type_tune, set_roof_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Roof?"));
    lcd_lib_update_screen();
}

static void use_bottom()
{
    lcd_question_screen(lcd_advanced_type_tune, set_bottom_true, PSTR("YES"), lcd_advanced_type_tune, set_bottom_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Bottom?"));
    lcd_lib_update_screen();
}

static void use_outer()
{
    lcd_question_screen(lcd_advanced_type_tune, set_outer_true, PSTR("YES"), lcd_advanced_type_tune, set_outer_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Outer?"));
    lcd_lib_update_screen();
}

static void use_inner()
{
    lcd_question_screen(lcd_advanced_type_tune, set_inner_true, PSTR("YES"), lcd_advanced_type_tune, set_inner_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Inner?"));
    lcd_lib_update_screen();
}

static void use_infill()
{
    lcd_question_screen(lcd_advanced_type_tune, set_infill_true, PSTR("YES"), lcd_advanced_type_tune, set_infill_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Infill?"));
    lcd_lib_update_screen();
}

static void use_top()
{
    lcd_question_screen(lcd_advanced_type_tune, set_top_true, PSTR("YES"), lcd_advanced_type_tune, set_top_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Top?"));
    lcd_lib_update_screen();
}

static void use_floor()
{
    lcd_question_screen(lcd_advanced_type_tune, set_floor_true, PSTR("YES"), lcd_advanced_type_tune, set_floor_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Floor?"));
    lcd_lib_update_screen();
}

static void use_travel()
{
    lcd_question_screen(lcd_advanced_type_tune, set_travel_true, PSTR("YES"), lcd_advanced_type_tune, set_travel_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Travel?"));
    lcd_lib_update_screen();
}


static void use_retract()
{
    lcd_question_screen(lcd_advanced_type_tune, set_retract_true, PSTR("YES"), lcd_advanced_type_tune, set_retract_false, PSTR("NO"));
    lcd_lib_draw_string_centerP(20, PSTR("Use Retract?"));
    lcd_lib_update_screen();
}