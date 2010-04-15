/*!
 * \file interface.c
 * \author Copyright 2207, 2008, 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief File for pcb-gfpw user interface building functions (GTK UI).
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.\n
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)


#include "gtk/about_dialog.c"

GtkWidget*
create_pcb_gfpw (void)
{
  GtkWidget *pcb_gfpw;
  GdkPixbuf *pcb_gfpw_icon_pixbuf;
  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *notebook;
  GtkWidget *footprint_tab_table;
  GtkWidget *author_frame;
  GtkWidget *author_frame_alignment;
  GtkWidget *author_table;
  GtkWidget *footprint_author_label;
  GtkWidget *footprint_dist_license_label;
  GtkWidget *footprint_author_entry;
  GtkWidget *footprint_dist_license_entry;
  GtkWidget *footprint_use_license_entry;
  GtkWidget *footprint_use_license_label;
  GtkWidget *footprint_status_label;
  GtkWidget *footprint_status_entry;
  GtkWidget *author_frame_label;
  GtkWidget *footprint_frame;
  GtkWidget *footprint_frame_alignment;
  GtkWidget *footprint_table;
  GtkWidget *footprint_units_label;
  GtkWidget *footprint_units_entry;
  GtkWidget *footprint_name_entry;
  GtkWidget *footprint_type_entry;
  GtkWidget *footprint_type_label;
  GtkWidget *footprint_name_label;
  GtkWidget *package_body_height_entry;
  GtkWidget *package_body_height_label;
  GtkWidget *pacakge_body_width_label;
  GtkWidget *package_body_length_label;
  GtkWidget *footprint_value_label;
  GtkWidget *package_body_width_entry;
  GtkWidget *package_body_length_entry;
  GtkWidget *footprint_value_entry;
  GtkWidget *footprint_refdes_label;
  GtkWidget *footprint_refdes_entry;
  GtkWidget *add_license_checkbutton;
  GtkWidget *package_is_radial_checkbutton;
  GtkWidget *add_attribs_checkbutton;
  GtkWidget *footprint_frame_label;
  GtkWidget *footprint_tab_label;
  GtkWidget *pins_pads_table;
  GtkWidget *pads_frame;
  GtkWidget *pads_alignment;
  GtkWidget *pads_table;
  GtkWidget *pad_solder_mask_clearance_label;
  GtkWidget *pad_solder_mask_clearance_entry;
  GtkWidget *pad_clearance_label;
  GtkWidget *pad_width_label;
  GtkWidget *pad_length_label;
  GtkWidget *pad_clearance_entry;
  GtkWidget *pad_width_entry;
  GtkWidget *pad_length_entry;
  GtkWidget *pad_shape_label;
  GtkWidget *pad_shape_entry;
  GtkWidget *pads_label;
  GtkWidget *pins_frame;
  GtkWidget *pins_alignment;
  GtkWidget *pins_table;
  GtkWidget *pad_diameter_entry;
  GtkWidget *pin_drill_diameter_label;
  GtkWidget *pin_pad_diameter_label;
  GtkWidget *pin_square_checkbutton;
  GtkWidget *pin_drill_diameter_entry;
  GtkWidget *pins_label;
  GtkWidget *pins_pads_pattern_frame;
  GtkWidget *pins_pads_pattern_alignment;
  GtkWidget *pins_pads_pattern_table;
  GtkWidget *total_pins_and_pads_label;
  GtkWidget *pitch_x_label;
  GtkWidget *pitch_y_label;
  GtkWidget *number_total_pins_entry;
  GtkWidget *pitch_x_entry;
  GtkWidget *pitch_y_entry;
  GtkWidget *label1;
  GtkWidget *label2;
  GtkWidget *count_x_entry;
  GtkWidget *count_y_entry;
  GtkWidget *number_1_position_label;
  GtkWidget *number_1_position_entry;
  GtkWidget *number_of_columns_label;
  GtkWidget *number_of_columns_entry;
  GtkWidget *number_of_rows_label;
  GtkWidget *number_of_rows_entry;
  GtkWidget *pin_pad_exceptions_entry;
  GtkWidget *pin_pad_exceptions_button;
  GtkWidget *pins_pads_pattern_label;
  GtkWidget *pins_pads_tab_tab_label;
  GtkWidget *silkscreen_table;
  GtkWidget *courtyard_frame;
  GtkWidget *courtyard_alignment;
  GtkWidget *courtyard_table;
  GtkWidget *courtyard_checkbutton;
  GtkWidget *courtyard_width_label;
  GtkWidget *courtyard_length_label;
  GtkWidget *courtyard_length_entry;
  GtkWidget *courtyard_width_entry;
  GtkWidget *courtyard_line_width_label;
  GtkWidget *courtyard_line_width_entry;
  GtkWidget *courtyard_clearance_with_package_label;
  GtkWidget *courtyard_clearance_with_package_entry;
  GtkWidget *courtyard_label;
  GtkWidget *package_frame;
  GtkWidget *package_alignment;
  GtkWidget *package_table;
  GtkWidget *silkscreen_package_outline_checkbutton;
  GtkWidget *silkscreen_indicate_1_checkbutton;
  GtkWidget *silkscreen_line_width_label;
  GtkWidget *silkscreen_line_width_entry;
  GtkWidget *package_label;
  GtkWidget *silkscreen_tab_label;
  GtkWidget *thermal_table;
  GtkWidget *thermal_pad_frame;
  GtkWidget *thermal_pad_alignment;
  GtkWidget *thermal_pad_table;
  GtkWidget *thermal_checkbutton;
  GtkWidget *thermal_pad_length_label;
  GtkWidget *thermal_pad_width_label;
  GtkWidget *thermal_width_entry;
  GtkWidget *thermal_length_entry;
  GtkWidget *thermal_nopaste_checkbutton;
  GtkWidget *thermal_pad_solder_mask_clearance_label;
  GtkWidget *thermal_pad_clearance_label;
  GtkWidget *thermal_solder_mask_clearance_entry;
  GtkWidget *thermal_clearance_entry;
  GtkWidget *thermal_pad_label;
  GtkWidget *fiducials_frame;
  GtkWidget *fiducials_alignment;
  GtkWidget *fiducials_table;
  GtkWidget *fiducial_pad_diameter_label;
  GtkWidget *fiducial_pad_diameter_entry;
  GtkWidget *fiducial_checkbutton;
  GtkWidget *fiducial_solder_mask_clearance_label;
  GtkWidget *fiducial_pad_solder_mask_clearance_entry;
  GtkWidget *fiducial_pad_clearance_label;
  GtkWidget *fiducial_pad_clearance_entry;
  GtkWidget *fiducials_label;
  GtkWidget *thermal_pad_tab_label;
  GtkWidget *heel_and_toe_goals_vbox;
  GtkWidget *top_to_bottom_frame;
  GtkWidget *top_to_bottom_alignment;
  GtkWidget *top_to_bottom_table;
  GtkWidget *G1_radiobutton;
  GSList *G1_radiobutton_group = NULL;
  GtkWidget *C1_radiobutton;
  GtkWidget *Z1_radiobutton;
  GtkWidget *G1_entry;
  GtkWidget *C1_entry;
  GtkWidget *Z1_entry;
  GtkWidget *top_to_bottom_label;
  GtkWidget *left_to_right_frame;
  GtkWidget *left_to_right_alignment;
  GtkWidget *left_to_right_table;
  GtkWidget *G2_radiobutton;
  GSList *G2_radiobutton_group = NULL;
  GtkWidget *C2_radiobutton;
  GtkWidget *Z2_radiobutton;
  GtkWidget *G2_entry;
  GtkWidget *C2_entry;
  GtkWidget *Z2_entry;
  GtkWidget *left_to_right_label;
  GtkWidget *heel_and_toe_goals_tab_label;
  GtkWidget *hbuttonbox0;
  GtkWidget *refresh_button;
  GtkWidget *dimensions_button;
  GtkWidget *alignment4;
  GtkWidget *hbox4;
  GtkWidget *image4;
  GtkWidget *label6;
  GtkWidget *preview_button;
  GtkWidget *alignment1;
  GtkWidget *hbox1;
  GtkWidget *image1;
  GtkWidget *label3;
  GtkWidget *clear_button;
  GtkWidget *hbuttonbox1;
  GtkWidget *close_button;
  GtkWidget *footprint_button;
  GtkWidget *alignment3;
  GtkWidget *hbox3;
  GtkWidget *image3;
  GtkWidget *label5;
  GtkWidget *open_button;
  GtkWidget *save_button;
  GtkWidget *statusbar;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  pcb_gfpw = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (pcb_gfpw, "pcb_gfpw");
  gtk_tooltips_set_tip (tooltips, pcb_gfpw, _("FootPrintWizard for pcb footprints"), NULL);
  gtk_window_set_title (GTK_WINDOW (pcb_gfpw), _("pcb-gfpw FootPrint Wizard"));
  pcb_gfpw_icon_pixbuf = create_pixbuf ("gFootprintWizard.xpm");
  if (pcb_gfpw_icon_pixbuf)
    {
      gtk_window_set_icon (GTK_WINDOW (pcb_gfpw), pcb_gfpw_icon_pixbuf);
      gdk_pixbuf_unref (pcb_gfpw_icon_pixbuf);
    }

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox, "vbox");
  gtk_widget_show (vbox);
  gtk_container_add (GTK_CONTAINER (pcb_gfpw), vbox);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_widget_set_name (hbox, "hbox");
  gtk_widget_show (hbox);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);

  notebook = gtk_notebook_new ();
  gtk_widget_set_name (notebook, "notebook");
  gtk_widget_show (notebook);
  gtk_box_pack_start (GTK_BOX (hbox), notebook, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (notebook), 10);

  footprint_tab_table = gtk_table_new (2, 1, FALSE);
  gtk_widget_set_name (footprint_tab_table, "footprint_tab_table");
  gtk_widget_show (footprint_tab_table);
  gtk_container_add (GTK_CONTAINER (notebook), footprint_tab_table);
  gtk_notebook_set_tab_label_packing (GTK_NOTEBOOK (notebook), footprint_tab_table,
                                      FALSE, FALSE, GTK_PACK_START);
  gtk_container_set_border_width (GTK_CONTAINER (footprint_tab_table), 5);
  gtk_table_set_row_spacings (GTK_TABLE (footprint_tab_table), 10);

  author_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (author_frame, "author_frame");
  gtk_widget_show (author_frame);
  gtk_table_attach (GTK_TABLE (footprint_tab_table), author_frame, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (author_frame), GTK_SHADOW_NONE);

  author_frame_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (author_frame_alignment, "author_frame_alignment");
  gtk_widget_show (author_frame_alignment);
  gtk_container_add (GTK_CONTAINER (author_frame), author_frame_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (author_frame_alignment), 0, 0, 12, 0);

  author_table = gtk_table_new (4, 2, FALSE);
  gtk_widget_set_name (author_table, "author_table");
  gtk_widget_show (author_table);
  gtk_container_add (GTK_CONTAINER (author_frame_alignment), author_table);

  footprint_author_label = gtk_label_new (_("Author"));
  gtk_widget_set_name (footprint_author_label, "footprint_author_label");
  gtk_widget_show (footprint_author_label);
  gtk_table_attach (GTK_TABLE (author_table), footprint_author_label, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_author_label), 0, 0.5);

  footprint_dist_license_label = gtk_label_new (_("Distribution license "));
  gtk_widget_set_name (footprint_dist_license_label, "footprint_dist_license_label");
  gtk_widget_show (footprint_dist_license_label);
  gtk_table_attach (GTK_TABLE (author_table), footprint_dist_license_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_dist_license_label), 0, 0.5);

  footprint_author_entry = gtk_entry_new ();
  gtk_widget_set_name (footprint_author_entry, "footprint_author_entry");
  gtk_widget_show (footprint_author_entry);
  gtk_table_attach (GTK_TABLE (author_table), footprint_author_entry, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, footprint_author_entry, _("Type your name here"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (footprint_author_entry), 8226);

  footprint_dist_license_entry = gtk_entry_new ();
  gtk_widget_set_name (footprint_dist_license_entry, "footprint_dist_license_entry");
  gtk_widget_show (footprint_dist_license_entry);
  gtk_table_attach (GTK_TABLE (author_table), footprint_dist_license_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, footprint_dist_license_entry, _("License under which you distribute the file"), NULL);
  gtk_entry_set_text (GTK_ENTRY (footprint_dist_license_entry), _("GPL"));
  gtk_entry_set_invisible_char (GTK_ENTRY (footprint_dist_license_entry), 8226);

  footprint_use_license_entry = gtk_entry_new ();
  gtk_widget_set_name (footprint_use_license_entry, "footprint_use_license_entry");
  gtk_widget_show (footprint_use_license_entry);
  gtk_table_attach (GTK_TABLE (author_table), footprint_use_license_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, footprint_use_license_entry, _("Allowable usage"), NULL);
  gtk_entry_set_text (GTK_ENTRY (footprint_use_license_entry), _("unlimited"));
  gtk_entry_set_invisible_char (GTK_ENTRY (footprint_use_license_entry), 8226);

  footprint_use_license_label = gtk_label_new (_("Use license"));
  gtk_widget_set_name (footprint_use_license_label, "footprint_use_license_label");
  gtk_widget_show (footprint_use_license_label);
  gtk_table_attach (GTK_TABLE (author_table), footprint_use_license_label, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_use_license_label), 0, 0.5);

  footprint_status_label = gtk_label_new (_("Status"));
  gtk_widget_set_name (footprint_status_label, "footprint_status_label");
  gtk_widget_show (footprint_status_label);
  gtk_table_attach (GTK_TABLE (author_table), footprint_status_label, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_status_label), 0, 0.5);

  footprint_status_entry = gtk_combo_box_entry_new_text ();
  gtk_widget_set_name (footprint_status_entry, "footprint_status_entry");
  gtk_widget_show (footprint_status_entry);
  gtk_table_attach (GTK_TABLE (author_table), footprint_status_entry, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_status_entry), "");
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_status_entry), _("Experimental"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_status_entry), _("Private (not published)"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_status_entry), _("Public (released)"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_status_entry), _("Stable (confirmed by peers)"));

  author_frame_label = gtk_label_new (_("<b>Author</b>"));
  gtk_widget_set_name (author_frame_label, "author_frame_label");
  gtk_widget_show (author_frame_label);
  gtk_frame_set_label_widget (GTK_FRAME (author_frame), author_frame_label);
  gtk_label_set_use_markup (GTK_LABEL (author_frame_label), TRUE);

  footprint_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (footprint_frame, "footprint_frame");
  gtk_widget_show (footprint_frame);
  gtk_table_attach (GTK_TABLE (footprint_tab_table), footprint_frame, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (footprint_frame), GTK_SHADOW_NONE);

  footprint_frame_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (footprint_frame_alignment, "footprint_frame_alignment");
  gtk_widget_show (footprint_frame_alignment);
  gtk_container_add (GTK_CONTAINER (footprint_frame), footprint_frame_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (footprint_frame_alignment), 0, 0, 12, 0);

  footprint_table = gtk_table_new (11, 2, FALSE);
  gtk_widget_set_name (footprint_table, "footprint_table");
  gtk_widget_show (footprint_table);
  gtk_container_add (GTK_CONTAINER (footprint_frame_alignment), footprint_table);

  footprint_units_label = gtk_label_new (_("Units"));
  gtk_widget_set_name (footprint_units_label, "footprint_units_label");
  gtk_widget_show (footprint_units_label);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_units_label, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_units_label), 0, 0.5);

  footprint_units_entry = gtk_combo_box_entry_new_text ();
  gtk_widget_set_name (footprint_units_entry, "footprint_units_entry");
  gtk_widget_show (footprint_units_entry);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_units_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_units_entry), "");
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_units_entry), _("mil"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_units_entry), _("mil/100"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_units_entry), _("mm"));

  footprint_name_entry = gtk_entry_new ();
  gtk_widget_set_name (footprint_name_entry, "footprint_name_entry");
  gtk_widget_show (footprint_name_entry);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_name_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, footprint_name_entry, _("Type the name of the footprint here, no suffix please"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (footprint_name_entry), 8226);

  footprint_type_entry = gtk_combo_box_entry_new_text ();
  gtk_widget_set_name (footprint_type_entry, "footprint_type_entry");
  gtk_widget_show (footprint_type_entry);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_type_entry, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), "");
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("BGA"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CAPA"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CAPAE"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CAPC"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CAPM"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CAPMP"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CON_DIL"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CON_DIP"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CON_HDR"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("CON_SIL"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("DIL"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("DIOM"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("DIOMELF"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("DIP"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("DO"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("INDC"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("INDM"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("INDP"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("PGA"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("PLCC"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("QFN"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("QFP"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("RES"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("RESC"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("RESM"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("RESMELF"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("SIL"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("SIP"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("SO"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("SOT"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("TO"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("TO92"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("TO220"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("TO220S"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("TO220SW"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (footprint_type_entry), _("TO220W"));

  footprint_type_label = gtk_label_new (_("Type"));
  gtk_widget_set_name (footprint_type_label, "footprint_type_label");
  gtk_widget_show (footprint_type_label);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_type_label, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_type_label), 0, 0.5);

  footprint_name_label = gtk_label_new (_("Name"));
  gtk_widget_set_name (footprint_name_label, "footprint_name_label");
  gtk_widget_show (footprint_name_label);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_name_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_name_label), 0, 0.5);

  package_body_height_entry = gtk_entry_new ();
  gtk_widget_set_name (package_body_height_entry, "package_body_height_entry");
  gtk_widget_show (package_body_height_entry);
  gtk_table_attach (GTK_TABLE (footprint_table), package_body_height_entry, 1, 2, 7, 8,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, package_body_height_entry, _("Type the height dimension of the package body here"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (package_body_height_entry), 8226);

  package_body_height_label = gtk_label_new (_("Body height (Z) "));
  gtk_widget_set_name (package_body_height_label, "package_body_height_label");
  gtk_widget_show (package_body_height_label);
  gtk_table_attach (GTK_TABLE (footprint_table), package_body_height_label, 0, 1, 7, 8,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (package_body_height_label), 0, 0.5);

  pacakge_body_width_label = gtk_label_new (_("Body width (Y)"));
  gtk_widget_set_name (pacakge_body_width_label, "pacakge_body_width_label");
  gtk_widget_show (pacakge_body_width_label);
  gtk_table_attach (GTK_TABLE (footprint_table), pacakge_body_width_label, 0, 1, 6, 7,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pacakge_body_width_label), 0, 0.5);

  package_body_length_label = gtk_label_new (_("Body length (X)"));
  gtk_widget_set_name (package_body_length_label, "package_body_length_label");
  gtk_widget_show (package_body_length_label);
  gtk_table_attach (GTK_TABLE (footprint_table), package_body_length_label, 0, 1, 5, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (package_body_length_label), 0, 0.5);

  footprint_value_label = gtk_label_new (_("Value"));
  gtk_widget_set_name (footprint_value_label, "footprint_value_label");
  gtk_widget_show (footprint_value_label);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_value_label, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_value_label), 0, 0.5);

  package_body_width_entry = gtk_entry_new ();
  gtk_widget_set_name (package_body_width_entry, "package_body_width_entry");
  gtk_widget_show (package_body_width_entry);
  gtk_table_attach (GTK_TABLE (footprint_table), package_body_width_entry, 1, 2, 6, 7,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, package_body_width_entry, _("Type the width dimension of the package body here"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (package_body_width_entry), 8226);

  package_body_length_entry = gtk_entry_new ();
  gtk_widget_set_name (package_body_length_entry, "package_body_length_entry");
  gtk_widget_show (package_body_length_entry);
  gtk_table_attach (GTK_TABLE (footprint_table), package_body_length_entry, 1, 2, 5, 6,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, package_body_length_entry, _("Type the length dimension of the package body here"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (package_body_length_entry), 8226);

  footprint_value_entry = gtk_entry_new ();
  gtk_widget_set_name (footprint_value_entry, "footprint_value_entry");
  gtk_widget_show (footprint_value_entry);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_value_entry, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, footprint_value_entry, _("Type the value of the package here"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (footprint_value_entry), 8226);

  footprint_refdes_label = gtk_label_new (_("Refdes prefix"));
  gtk_widget_set_name (footprint_refdes_label, "footprint_refdes_label");
  gtk_widget_show (footprint_refdes_label);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_refdes_label, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (footprint_refdes_label), 0, 0.5);

  footprint_refdes_entry = gtk_entry_new ();
  gtk_widget_set_name (footprint_refdes_entry, "footprint_refdes_entry");
  gtk_widget_show (footprint_refdes_entry);
  gtk_table_attach (GTK_TABLE (footprint_table), footprint_refdes_entry, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, footprint_refdes_entry, _("Type a refdes prefix here, without the ? please"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (footprint_refdes_entry), 8226);

  add_license_checkbutton = gtk_check_button_new_with_mnemonic (_("Add license to footprint"));
  gtk_widget_set_name (add_license_checkbutton, "add_license_checkbutton");
  gtk_widget_show (add_license_checkbutton);
  gtk_table_attach (GTK_TABLE (footprint_table), add_license_checkbutton, 0, 2, 9, 10,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, add_license_checkbutton, _("Check to add a license text to the footprint."), NULL);

  package_is_radial_checkbutton = gtk_check_button_new_with_mnemonic (_("Radial package "));
  gtk_widget_set_name (package_is_radial_checkbutton, "package_is_radial_checkbutton");
  gtk_widget_show (package_is_radial_checkbutton);
  gtk_table_attach (GTK_TABLE (footprint_table), package_is_radial_checkbutton, 0, 2, 8, 9,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, package_is_radial_checkbutton, _("Check for a radial package"), NULL);

  add_attribs_checkbutton = gtk_check_button_new_with_mnemonic (_("Add attributes to footprint"));
  gtk_widget_set_name (add_attribs_checkbutton, "add_attribs_checkbutton");
  gtk_widget_show (add_attribs_checkbutton);
  gtk_table_attach (GTK_TABLE (footprint_table), add_attribs_checkbutton, 0, 2, 10, 11,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, add_attribs_checkbutton, _("Check to add attributes to the footprint."), NULL);

  footprint_frame_label = gtk_label_new (_("<b>Footprint</b>"));
  gtk_widget_set_name (footprint_frame_label, "footprint_frame_label");
  gtk_widget_show (footprint_frame_label);
  gtk_frame_set_label_widget (GTK_FRAME (footprint_frame), footprint_frame_label);
  gtk_label_set_use_markup (GTK_LABEL (footprint_frame_label), TRUE);

  footprint_tab_label = gtk_label_new (_("Footprint"));
  gtk_widget_set_name (footprint_tab_label, "footprint_tab_label");
  gtk_widget_show (footprint_tab_label);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 0), footprint_tab_label);

  pins_pads_table = gtk_table_new (3, 1, FALSE);
  gtk_widget_set_name (pins_pads_table, "pins_pads_table");
  gtk_widget_show (pins_pads_table);
  gtk_container_add (GTK_CONTAINER (notebook), pins_pads_table);
  gtk_notebook_set_tab_label_packing (GTK_NOTEBOOK (notebook), pins_pads_table,
                                      FALSE, FALSE, GTK_PACK_START);
  gtk_container_set_border_width (GTK_CONTAINER (pins_pads_table), 5);
  gtk_table_set_row_spacings (GTK_TABLE (pins_pads_table), 10);

  pads_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (pads_frame, "pads_frame");
  gtk_widget_show (pads_frame);
  gtk_table_attach (GTK_TABLE (pins_pads_table), pads_frame, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (pads_frame), GTK_SHADOW_NONE);

  pads_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (pads_alignment, "pads_alignment");
  gtk_widget_show (pads_alignment);
  gtk_container_add (GTK_CONTAINER (pads_frame), pads_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (pads_alignment), 0, 0, 12, 0);

  pads_table = gtk_table_new (5, 2, FALSE);
  gtk_widget_set_name (pads_table, "pads_table");
  gtk_widget_show (pads_table);
  gtk_container_add (GTK_CONTAINER (pads_alignment), pads_table);

  pad_solder_mask_clearance_label = gtk_label_new (_("Pad solder mask clearance "));
  gtk_widget_set_name (pad_solder_mask_clearance_label, "pad_solder_mask_clearance_label");
  gtk_widget_show (pad_solder_mask_clearance_label);
  gtk_table_attach (GTK_TABLE (pads_table), pad_solder_mask_clearance_label, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pad_solder_mask_clearance_label), 0, 0.5);

  pad_solder_mask_clearance_entry = gtk_entry_new ();
  gtk_widget_set_name (pad_solder_mask_clearance_entry, "pad_solder_mask_clearance_entry");
  gtk_widget_show (pad_solder_mask_clearance_entry);
  gtk_table_attach (GTK_TABLE (pads_table), pad_solder_mask_clearance_entry, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pad_solder_mask_clearance_entry, _("Clearance distance with solder mask"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pad_solder_mask_clearance_entry), 8226);

  pad_clearance_label = gtk_label_new (_("Pad clearance"));
  gtk_widget_set_name (pad_clearance_label, "pad_clearance_label");
  gtk_widget_show (pad_clearance_label);
  gtk_table_attach (GTK_TABLE (pads_table), pad_clearance_label, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pad_clearance_label), 0, 0.5);

  pad_width_label = gtk_label_new (_("Pad width (Y)"));
  gtk_widget_set_name (pad_width_label, "pad_width_label");
  gtk_widget_show (pad_width_label);
  gtk_table_attach (GTK_TABLE (pads_table), pad_width_label, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pad_width_label), 0, 0.5);

  pad_length_label = gtk_label_new (_("Pad length (X) "));
  gtk_widget_set_name (pad_length_label, "pad_length_label");
  gtk_widget_show (pad_length_label);
  gtk_table_attach (GTK_TABLE (pads_table), pad_length_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pad_length_label), 0, 0.5);

  pad_clearance_entry = gtk_entry_new ();
  gtk_widget_set_name (pad_clearance_entry, "pad_clearance_entry");
  gtk_widget_show (pad_clearance_entry);
  gtk_table_attach (GTK_TABLE (pads_table), pad_clearance_entry, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pad_clearance_entry, _("Clearance distance with polygons"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pad_clearance_entry), 8226);

  pad_width_entry = gtk_entry_new ();
  gtk_widget_set_name (pad_width_entry, "pad_width_entry");
  gtk_widget_show (pad_width_entry);
  gtk_table_attach (GTK_TABLE (pads_table), pad_width_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pad_width_entry, _("Width of pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pad_width_entry), 8226);

  pad_length_entry = gtk_entry_new ();
  gtk_widget_set_name (pad_length_entry, "pad_length_entry");
  gtk_widget_show (pad_length_entry);
  gtk_table_attach (GTK_TABLE (pads_table), pad_length_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pad_length_entry, _("Length of pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pad_length_entry), 8226);

  pad_shape_label = gtk_label_new (_("Pad shape"));
  gtk_widget_set_name (pad_shape_label, "pad_shape_label");
  gtk_widget_show (pad_shape_label);
  gtk_table_attach (GTK_TABLE (pads_table), pad_shape_label, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pad_shape_label), 0, 0.5);

  pad_shape_entry = gtk_combo_box_entry_new_text ();
  gtk_widget_set_name (pad_shape_entry, "pad_shape_entry");
  gtk_widget_show (pad_shape_entry);
  gtk_table_attach (GTK_TABLE (pads_table), pad_shape_entry, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_combo_box_append_text (GTK_COMBO_BOX (pad_shape_entry), "");
  gtk_combo_box_append_text (GTK_COMBO_BOX (pad_shape_entry), _("circular pad"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (pad_shape_entry), _("rectangular pad"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (pad_shape_entry), _("octagonal pad"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (pad_shape_entry), _("rounded pad, elongated"));

  pads_label = gtk_label_new (_("<b>Pads</b>"));
  gtk_widget_set_name (pads_label, "pads_label");
  gtk_widget_show (pads_label);
  gtk_frame_set_label_widget (GTK_FRAME (pads_frame), pads_label);
  gtk_label_set_use_markup (GTK_LABEL (pads_label), TRUE);

  pins_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (pins_frame, "pins_frame");
  gtk_widget_show (pins_frame);
  gtk_table_attach (GTK_TABLE (pins_pads_table), pins_frame, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (pins_frame), GTK_SHADOW_NONE);

  pins_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (pins_alignment, "pins_alignment");
  gtk_widget_show (pins_alignment);
  gtk_container_add (GTK_CONTAINER (pins_frame), pins_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (pins_alignment), 0, 0, 12, 0);

  pins_table = gtk_table_new (3, 2, FALSE);
  gtk_widget_set_name (pins_table, "pins_table");
  gtk_widget_show (pins_table);
  gtk_container_add (GTK_CONTAINER (pins_alignment), pins_table);

  pad_diameter_entry = gtk_entry_new ();
  gtk_widget_set_name (pad_diameter_entry, "pad_diameter_entry");
  gtk_widget_show (pad_diameter_entry);
  gtk_table_attach (GTK_TABLE (pins_table), pad_diameter_entry, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pad_diameter_entry, _("Diameter of pad for pins"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pad_diameter_entry), 8226);

  pin_drill_diameter_label = gtk_label_new (_("Pin drill diameter (d) "));
  gtk_widget_set_name (pin_drill_diameter_label, "pin_drill_diameter_label");
  gtk_widget_show (pin_drill_diameter_label);
  gtk_table_attach (GTK_TABLE (pins_table), pin_drill_diameter_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pin_drill_diameter_label), 0, 0.5);

  pin_pad_diameter_label = gtk_label_new (_("Pin pad diameter (D) "));
  gtk_widget_set_name (pin_pad_diameter_label, "pin_pad_diameter_label");
  gtk_widget_show (pin_pad_diameter_label);
  gtk_table_attach (GTK_TABLE (pins_table), pin_pad_diameter_label, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pin_pad_diameter_label), 0, 0.5);

  pin_square_checkbutton = gtk_check_button_new_with_mnemonic (_("Pin #1 square "));
  gtk_widget_set_name (pin_square_checkbutton, "pin_square_checkbutton");
  gtk_widget_show (pin_square_checkbutton);
  gtk_table_attach (GTK_TABLE (pins_table), pin_square_checkbutton, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pin_square_checkbutton, _("Check to draw square pin #1"), NULL);

  pin_drill_diameter_entry = gtk_entry_new ();
  gtk_widget_set_name (pin_drill_diameter_entry, "pin_drill_diameter_entry");
  gtk_widget_show (pin_drill_diameter_entry);
  gtk_table_attach (GTK_TABLE (pins_table), pin_drill_diameter_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_widget_set_size_request (pin_drill_diameter_entry, 158, -1);
  gtk_tooltips_set_tip (tooltips, pin_drill_diameter_entry, _("Diameter of drill hole for pins"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pin_drill_diameter_entry), 8226);

  pins_label = gtk_label_new (_("<b>Pins</b>"));
  gtk_widget_set_name (pins_label, "pins_label");
  gtk_widget_show (pins_label);
  gtk_frame_set_label_widget (GTK_FRAME (pins_frame), pins_label);
  gtk_label_set_use_markup (GTK_LABEL (pins_label), TRUE);

  pins_pads_pattern_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (pins_pads_pattern_frame, "pins_pads_pattern_frame");
  gtk_widget_show (pins_pads_pattern_frame);
  gtk_table_attach (GTK_TABLE (pins_pads_table), pins_pads_pattern_frame, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (pins_pads_pattern_frame), GTK_SHADOW_NONE);

  pins_pads_pattern_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (pins_pads_pattern_alignment, "pins_pads_pattern_alignment");
  gtk_widget_show (pins_pads_pattern_alignment);
  gtk_container_add (GTK_CONTAINER (pins_pads_pattern_frame), pins_pads_pattern_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (pins_pads_pattern_alignment), 0, 0, 12, 0);

  pins_pads_pattern_table = gtk_table_new (9, 2, FALSE);
  gtk_widget_set_name (pins_pads_pattern_table, "pins_pads_pattern_table");
  gtk_widget_show (pins_pads_pattern_table);
  gtk_container_add (GTK_CONTAINER (pins_pads_pattern_alignment), pins_pads_pattern_table);

  total_pins_and_pads_label = gtk_label_new (_("Total pins and pads "));
  gtk_widget_set_name (total_pins_and_pads_label, "total_pins_and_pads_label");
  gtk_widget_show (total_pins_and_pads_label);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), total_pins_and_pads_label, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (total_pins_and_pads_label), 0, 0.5);

  pitch_x_label = gtk_label_new (_("Pitch X-direction"));
  gtk_widget_set_name (pitch_x_label, "pitch_x_label");
  gtk_widget_show (pitch_x_label);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), pitch_x_label, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pitch_x_label), 0, 0.5);

  pitch_y_label = gtk_label_new (_("Pitch Y-direction"));
  gtk_widget_set_name (pitch_y_label, "pitch_y_label");
  gtk_widget_show (pitch_y_label);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), pitch_y_label, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (pitch_y_label), 0, 0.5);

  number_total_pins_entry = gtk_entry_new ();
  gtk_widget_set_name (number_total_pins_entry, "number_total_pins_entry");
  gtk_widget_show (number_total_pins_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), number_total_pins_entry, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, number_total_pins_entry, _("Total number of pins and pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (number_total_pins_entry), 8226);

  pitch_x_entry = gtk_entry_new ();
  gtk_widget_set_name (pitch_x_entry, "pitch_x_entry");
  gtk_widget_show (pitch_x_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), pitch_x_entry, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pitch_x_entry, _("Horizontal pin/pad pitch"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pitch_x_entry), 8226);

  pitch_y_entry = gtk_entry_new ();
  gtk_widget_set_name (pitch_y_entry, "pitch_y_entry");
  gtk_widget_show (pitch_y_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), pitch_y_entry, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pitch_y_entry, _("Vertical pin/pad pitch"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pitch_y_entry), 8226);

  label1 = gtk_label_new (_("Count X-direction"));
  gtk_widget_set_name (label1, "label1");
  gtk_widget_show (label1);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), label1, 0, 1, 5, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label1), 0, 0.5);

  label2 = gtk_label_new (_("Count Y-direction"));
  gtk_widget_set_name (label2, "label2");
  gtk_widget_show (label2);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), label2, 0, 1, 6, 7,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (label2), 0, 0.5);

  count_x_entry = gtk_entry_new ();
  gtk_widget_set_name (count_x_entry, "count_x_entry");
  gtk_widget_show (count_x_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), count_x_entry, 1, 2, 5, 6,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, count_x_entry, _("Number of horizontal pin/pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (count_x_entry), 8226);

  count_y_entry = gtk_entry_new ();
  gtk_widget_set_name (count_y_entry, "count_y_entry");
  gtk_widget_show (count_y_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), count_y_entry, 1, 2, 6, 7,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, count_y_entry, _("Number of vertical pin/pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (count_y_entry), 8226);

  number_1_position_label = gtk_label_new (_("Pin/pad #1 position "));
  gtk_widget_set_name (number_1_position_label, "number_1_position_label");
  gtk_widget_show (number_1_position_label);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), number_1_position_label, 0, 1, 7, 8,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (number_1_position_label), 0, 0.5);

  number_1_position_entry = gtk_combo_box_entry_new_text ();
  gtk_widget_set_name (number_1_position_entry, "number_1_position_entry");
  gtk_widget_show (number_1_position_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), number_1_position_entry, 1, 2, 7, 8,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), "");
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Upper left"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Middle left"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Lower left"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Upper middle"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Middle middle"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Lower middle"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Upper right"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Middle right"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _("Lower right"));
  gtk_combo_box_append_text (GTK_COMBO_BOX (number_1_position_entry), _(" "));

  number_of_columns_label = gtk_label_new (_("Columns"));
  gtk_widget_set_name (number_of_columns_label, "number_of_columns_label");
  gtk_widget_show (number_of_columns_label);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), number_of_columns_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (number_of_columns_label), 0, 0.5);

  number_of_columns_entry = gtk_entry_new ();
  gtk_widget_set_name (number_of_columns_entry, "number_of_columns_entry");
  gtk_widget_show (number_of_columns_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), number_of_columns_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, number_of_columns_entry, _("Number of columns"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (number_of_columns_entry), 8226);

  number_of_rows_label = gtk_label_new (_("Rows"));
  gtk_widget_set_name (number_of_rows_label, "number_of_rows_label");
  gtk_widget_show (number_of_rows_label);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), number_of_rows_label, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (number_of_rows_label), 0, 0.5);

  number_of_rows_entry = gtk_entry_new ();
  gtk_widget_set_name (number_of_rows_entry, "number_of_rows_entry");
  gtk_widget_show (number_of_rows_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), number_of_rows_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, number_of_rows_entry, _("Number of rows"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (number_of_rows_entry), 8226);

  pin_pad_exceptions_entry = gtk_entry_new ();
  gtk_widget_set_name (pin_pad_exceptions_entry, "pin_pad_exceptions_entry");
  gtk_widget_show (pin_pad_exceptions_entry);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), pin_pad_exceptions_entry, 1, 2, 8, 9,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pin_pad_exceptions_entry, _("Enter non-existing pins or pads here"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (pin_pad_exceptions_entry), 8226);

  pin_pad_exceptions_button = gtk_button_new_with_mnemonic (_("Pin/Pad exceptions"));
  gtk_widget_set_name (pin_pad_exceptions_button, "pin_pad_exceptions_button");
  gtk_widget_show (pin_pad_exceptions_button);
  gtk_table_attach (GTK_TABLE (pins_pads_pattern_table), pin_pad_exceptions_button, 0, 1, 8, 9,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, pin_pad_exceptions_button, _("Click to select pin/pad exceptions"), NULL);

  pins_pads_pattern_label = gtk_label_new (_("<b>Pattern</b>"));
  gtk_widget_set_name (pins_pads_pattern_label, "pins_pads_pattern_label");
  gtk_widget_show (pins_pads_pattern_label);
  gtk_frame_set_label_widget (GTK_FRAME (pins_pads_pattern_frame), pins_pads_pattern_label);
  gtk_label_set_use_markup (GTK_LABEL (pins_pads_pattern_label), TRUE);

  pins_pads_tab_tab_label = gtk_label_new (_("Pins/Pads"));
  gtk_widget_set_name (pins_pads_tab_tab_label, "pins_pads_tab_tab_label");
  gtk_widget_show (pins_pads_tab_tab_label);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 1), pins_pads_tab_tab_label);

  silkscreen_table = gtk_table_new (2, 1, FALSE);
  gtk_widget_set_name (silkscreen_table, "silkscreen_table");
  gtk_widget_show (silkscreen_table);
  gtk_container_add (GTK_CONTAINER (notebook), silkscreen_table);
  gtk_notebook_set_tab_label_packing (GTK_NOTEBOOK (notebook), silkscreen_table,
                                      FALSE, FALSE, GTK_PACK_START);
  gtk_container_set_border_width (GTK_CONTAINER (silkscreen_table), 5);
  gtk_table_set_row_spacings (GTK_TABLE (silkscreen_table), 10);

  courtyard_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (courtyard_frame, "courtyard_frame");
  gtk_widget_show (courtyard_frame);
  gtk_table_attach (GTK_TABLE (silkscreen_table), courtyard_frame, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (courtyard_frame), GTK_SHADOW_NONE);

  courtyard_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (courtyard_alignment, "courtyard_alignment");
  gtk_widget_show (courtyard_alignment);
  gtk_container_add (GTK_CONTAINER (courtyard_frame), courtyard_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (courtyard_alignment), 0, 0, 12, 0);

  courtyard_table = gtk_table_new (5, 2, FALSE);
  gtk_widget_set_name (courtyard_table, "courtyard_table");
  gtk_widget_show (courtyard_table);
  gtk_container_add (GTK_CONTAINER (courtyard_alignment), courtyard_table);

  courtyard_checkbutton = gtk_check_button_new_with_mnemonic (_("Print courtyard "));
  gtk_widget_set_name (courtyard_checkbutton, "courtyard_checkbutton");
  gtk_widget_show (courtyard_checkbutton);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_checkbutton, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, courtyard_checkbutton, _("Check to draw a courtyard (keepout)"), NULL);

  courtyard_width_label = gtk_label_new (_("Width (Y)"));
  gtk_widget_set_name (courtyard_width_label, "courtyard_width_label");
  gtk_widget_show (courtyard_width_label);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_width_label, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (courtyard_width_label), 0, 0.5);

  courtyard_length_label = gtk_label_new (_("Length or diameter (X) "));
  gtk_widget_set_name (courtyard_length_label, "courtyard_length_label");
  gtk_widget_show (courtyard_length_label);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_length_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (courtyard_length_label), 0, 0.5);

  courtyard_length_entry = gtk_entry_new ();
  gtk_widget_set_name (courtyard_length_entry, "courtyard_length_entry");
  gtk_widget_show (courtyard_length_entry);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_length_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, courtyard_length_entry, _("Length of courtyard"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (courtyard_length_entry), 8226);

  courtyard_width_entry = gtk_entry_new ();
  gtk_widget_set_name (courtyard_width_entry, "courtyard_width_entry");
  gtk_widget_show (courtyard_width_entry);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_width_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, courtyard_width_entry, _("Width of courtyard"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (courtyard_width_entry), 8226);

  courtyard_line_width_label = gtk_label_new (_("Line width"));
  gtk_widget_set_name (courtyard_line_width_label, "courtyard_line_width_label");
  gtk_widget_show (courtyard_line_width_label);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_line_width_label, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (courtyard_line_width_label), 0, 0.5);

  courtyard_line_width_entry = gtk_entry_new ();
  gtk_widget_set_name (courtyard_line_width_entry, "courtyard_line_width_entry");
  gtk_widget_show (courtyard_line_width_entry);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_line_width_entry, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, courtyard_line_width_entry, _("Line width for courtyard"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (courtyard_line_width_entry), 8226);

  courtyard_clearance_with_package_label = gtk_label_new (_("Clearance with package "));
  gtk_widget_set_name (courtyard_clearance_with_package_label, "courtyard_clearance_with_package_label");
  gtk_widget_show (courtyard_clearance_with_package_label);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_clearance_with_package_label, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (courtyard_clearance_with_package_label), 0, 0.5);

  courtyard_clearance_with_package_entry = gtk_entry_new ();
  gtk_widget_set_name (courtyard_clearance_with_package_entry, "courtyard_clearance_with_package_entry");
  gtk_widget_show (courtyard_clearance_with_package_entry);
  gtk_table_attach (GTK_TABLE (courtyard_table), courtyard_clearance_with_package_entry, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, courtyard_clearance_with_package_entry, _("Clearance distance with package"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (courtyard_clearance_with_package_entry), 8226);

  courtyard_label = gtk_label_new (_("<b>Courtyard</b>"));
  gtk_widget_set_name (courtyard_label, "courtyard_label");
  gtk_widget_show (courtyard_label);
  gtk_frame_set_label_widget (GTK_FRAME (courtyard_frame), courtyard_label);
  gtk_label_set_use_markup (GTK_LABEL (courtyard_label), TRUE);

  package_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (package_frame, "package_frame");
  gtk_widget_show (package_frame);
  gtk_table_attach (GTK_TABLE (silkscreen_table), package_frame, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (package_frame), GTK_SHADOW_NONE);

  package_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (package_alignment, "package_alignment");
  gtk_widget_show (package_alignment);
  gtk_container_add (GTK_CONTAINER (package_frame), package_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (package_alignment), 0, 0, 12, 0);

  package_table = gtk_table_new (2, 2, FALSE);
  gtk_widget_set_name (package_table, "package_table");
  gtk_widget_show (package_table);
  gtk_container_add (GTK_CONTAINER (package_alignment), package_table);

  silkscreen_package_outline_checkbutton = gtk_check_button_new_with_mnemonic (_("Print package outline "));
  gtk_widget_set_name (silkscreen_package_outline_checkbutton, "silkscreen_package_outline_checkbutton");
  gtk_widget_show (silkscreen_package_outline_checkbutton);
  gtk_table_attach (GTK_TABLE (package_table), silkscreen_package_outline_checkbutton, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, silkscreen_package_outline_checkbutton, _("Check to draw package outline"), NULL);

  silkscreen_indicate_1_checkbutton = gtk_check_button_new_with_mnemonic (_("Pin/Pad #1 indicator "));
  gtk_widget_set_name (silkscreen_indicate_1_checkbutton, "silkscreen_indicate_1_checkbutton");
  gtk_widget_show (silkscreen_indicate_1_checkbutton);
  gtk_table_attach (GTK_TABLE (package_table), silkscreen_indicate_1_checkbutton, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, silkscreen_indicate_1_checkbutton, _("Check to draw indicator for pin/pad #1"), NULL);

  silkscreen_line_width_label = gtk_label_new (_("Line width"));
  gtk_widget_set_name (silkscreen_line_width_label, "silkscreen_line_width_label");
  gtk_widget_show (silkscreen_line_width_label);
  gtk_table_attach (GTK_TABLE (package_table), silkscreen_line_width_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (silkscreen_line_width_label), 0, 0.5);

  silkscreen_line_width_entry = gtk_entry_new ();
  gtk_widget_set_name (silkscreen_line_width_entry, "silkscreen_line_width_entry");
  gtk_widget_show (silkscreen_line_width_entry);
  gtk_table_attach (GTK_TABLE (package_table), silkscreen_line_width_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, silkscreen_line_width_entry, _("Line width for silkscreen"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (silkscreen_line_width_entry), 8226);

  package_label = gtk_label_new (_("<b>Package</b>"));
  gtk_widget_set_name (package_label, "package_label");
  gtk_widget_show (package_label);
  gtk_frame_set_label_widget (GTK_FRAME (package_frame), package_label);
  gtk_label_set_use_markup (GTK_LABEL (package_label), TRUE);

  silkscreen_tab_label = gtk_label_new (_("Silkscreen"));
  gtk_widget_set_name (silkscreen_tab_label, "silkscreen_tab_label");
  gtk_widget_show (silkscreen_tab_label);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 2), silkscreen_tab_label);

  thermal_table = gtk_table_new (2, 1, FALSE);
  gtk_widget_set_name (thermal_table, "thermal_table");
  gtk_widget_show (thermal_table);
  gtk_container_add (GTK_CONTAINER (notebook), thermal_table);
  gtk_notebook_set_tab_label_packing (GTK_NOTEBOOK (notebook), thermal_table,
                                      FALSE, FALSE, GTK_PACK_START);
  gtk_container_set_border_width (GTK_CONTAINER (thermal_table), 5);
  gtk_table_set_row_spacings (GTK_TABLE (thermal_table), 10);

  thermal_pad_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (thermal_pad_frame, "thermal_pad_frame");
  gtk_widget_show (thermal_pad_frame);
  gtk_table_attach (GTK_TABLE (thermal_table), thermal_pad_frame, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (thermal_pad_frame), GTK_SHADOW_NONE);

  thermal_pad_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (thermal_pad_alignment, "thermal_pad_alignment");
  gtk_widget_show (thermal_pad_alignment);
  gtk_container_add (GTK_CONTAINER (thermal_pad_frame), thermal_pad_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (thermal_pad_alignment), 0, 0, 12, 0);

  thermal_pad_table = gtk_table_new (5, 2, FALSE);
  gtk_widget_set_name (thermal_pad_table, "thermal_pad_table");
  gtk_widget_show (thermal_pad_table);
  gtk_container_add (GTK_CONTAINER (thermal_pad_alignment), thermal_pad_table);

  thermal_checkbutton = gtk_check_button_new_with_mnemonic (_("Thermal pad"));
  gtk_widget_set_name (thermal_checkbutton, "thermal_checkbutton");
  gtk_widget_show (thermal_checkbutton);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_checkbutton, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, thermal_checkbutton, _("Check for a thermal pad"), NULL);

  thermal_pad_length_label = gtk_label_new (_("Pad length (X)"));
  gtk_widget_set_name (thermal_pad_length_label, "thermal_pad_length_label");
  gtk_widget_show (thermal_pad_length_label);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_pad_length_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (thermal_pad_length_label), 0, 0.5);

  thermal_pad_width_label = gtk_label_new (_("Pad width (Y)"));
  gtk_widget_set_name (thermal_pad_width_label, "thermal_pad_width_label");
  gtk_widget_show (thermal_pad_width_label);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_pad_width_label, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (thermal_pad_width_label), 0, 0.5);

  thermal_width_entry = gtk_entry_new ();
  gtk_widget_set_name (thermal_width_entry, "thermal_width_entry");
  gtk_widget_show (thermal_width_entry);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_width_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, thermal_width_entry, _("Width of thermal pad"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (thermal_width_entry), 8226);

  thermal_length_entry = gtk_entry_new ();
  gtk_widget_set_name (thermal_length_entry, "thermal_length_entry");
  gtk_widget_show (thermal_length_entry);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_length_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, thermal_length_entry, _("Length of thermal pad"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (thermal_length_entry), 8226);

  thermal_nopaste_checkbutton = gtk_check_button_new_with_mnemonic (_("No paste on pad"));
  gtk_widget_set_name (thermal_nopaste_checkbutton, "thermal_nopaste_checkbutton");
  gtk_widget_show (thermal_nopaste_checkbutton);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_nopaste_checkbutton, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, thermal_nopaste_checkbutton, _("Check for no paste on pad"), NULL);

  thermal_pad_solder_mask_clearance_label = gtk_label_new (_("Pad solder mask clearance "));
  gtk_widget_set_name (thermal_pad_solder_mask_clearance_label, "thermal_pad_solder_mask_clearance_label");
  gtk_widget_show (thermal_pad_solder_mask_clearance_label);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_pad_solder_mask_clearance_label, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (thermal_pad_solder_mask_clearance_label), 0, 0.5);

  thermal_pad_clearance_label = gtk_label_new (_("Pad Clearance "));
  gtk_widget_set_name (thermal_pad_clearance_label, "thermal_pad_clearance_label");
  gtk_widget_show (thermal_pad_clearance_label);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_pad_clearance_label, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (thermal_pad_clearance_label), 0, 0.5);

  thermal_solder_mask_clearance_entry = gtk_entry_new ();
  gtk_widget_set_name (thermal_solder_mask_clearance_entry, "thermal_solder_mask_clearance_entry");
  gtk_widget_show (thermal_solder_mask_clearance_entry);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_solder_mask_clearance_entry, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, thermal_solder_mask_clearance_entry, _("Clearance distance with solder mask"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (thermal_solder_mask_clearance_entry), 8226);

  thermal_clearance_entry = gtk_entry_new ();
  gtk_widget_set_name (thermal_clearance_entry, "thermal_clearance_entry");
  gtk_widget_show (thermal_clearance_entry);
  gtk_table_attach (GTK_TABLE (thermal_pad_table), thermal_clearance_entry, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, thermal_clearance_entry, _("Clearance distance with polygons"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (thermal_clearance_entry), 8226);

  thermal_pad_label = gtk_label_new (_("<b>Thermal pad</b>"));
  gtk_widget_set_name (thermal_pad_label, "thermal_pad_label");
  gtk_widget_show (thermal_pad_label);
  gtk_frame_set_label_widget (GTK_FRAME (thermal_pad_frame), thermal_pad_label);
  gtk_label_set_use_markup (GTK_LABEL (thermal_pad_label), TRUE);

  fiducials_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (fiducials_frame, "fiducials_frame");
  gtk_widget_show (fiducials_frame);
  gtk_table_attach (GTK_TABLE (thermal_table), fiducials_frame, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (fiducials_frame), GTK_SHADOW_NONE);

  fiducials_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (fiducials_alignment, "fiducials_alignment");
  gtk_widget_show (fiducials_alignment);
  gtk_container_add (GTK_CONTAINER (fiducials_frame), fiducials_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (fiducials_alignment), 0, 0, 12, 0);

  fiducials_table = gtk_table_new (4, 2, FALSE);
  gtk_widget_set_name (fiducials_table, "fiducials_table");
  gtk_widget_show (fiducials_table);
  gtk_container_add (GTK_CONTAINER (fiducials_alignment), fiducials_table);

  fiducial_pad_diameter_label = gtk_label_new (_("Fiducial pad diameter (D)"));
  gtk_widget_set_name (fiducial_pad_diameter_label, "fiducial_pad_diameter_label");
  gtk_widget_show (fiducial_pad_diameter_label);
  gtk_table_attach (GTK_TABLE (fiducials_table), fiducial_pad_diameter_label, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (fiducial_pad_diameter_label), 0, 0.5);

  fiducial_pad_diameter_entry = gtk_entry_new ();
  gtk_widget_set_name (fiducial_pad_diameter_entry, "fiducial_pad_diameter_entry");
  gtk_widget_show (fiducial_pad_diameter_entry);
  gtk_table_attach (GTK_TABLE (fiducials_table), fiducial_pad_diameter_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, fiducial_pad_diameter_entry, _("Diameter of fiducial pad"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (fiducial_pad_diameter_entry), 8226);

  fiducial_checkbutton = gtk_check_button_new_with_mnemonic (_("Fiducials"));
  gtk_widget_set_name (fiducial_checkbutton, "fiducial_checkbutton");
  gtk_widget_show (fiducial_checkbutton);
  gtk_table_attach (GTK_TABLE (fiducials_table), fiducial_checkbutton, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  fiducial_solder_mask_clearance_label = gtk_label_new (_("Fiducial solder mask clearance"));
  gtk_widget_set_name (fiducial_solder_mask_clearance_label, "fiducial_solder_mask_clearance_label");
  gtk_widget_show (fiducial_solder_mask_clearance_label);
  gtk_table_attach (GTK_TABLE (fiducials_table), fiducial_solder_mask_clearance_label, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (fiducial_solder_mask_clearance_label), 0, 0.5);

  fiducial_pad_solder_mask_clearance_entry = gtk_entry_new ();
  gtk_widget_set_name (fiducial_pad_solder_mask_clearance_entry, "fiducial_pad_solder_mask_clearance_entry");
  gtk_widget_show (fiducial_pad_solder_mask_clearance_entry);
  gtk_table_attach (GTK_TABLE (fiducials_table), fiducial_pad_solder_mask_clearance_entry, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, fiducial_pad_solder_mask_clearance_entry, _("Clearance distance with solder mask"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (fiducial_pad_solder_mask_clearance_entry), 8226);

  fiducial_pad_clearance_label = gtk_label_new (_("Fiducial Pad Clearance"));
  gtk_widget_set_name (fiducial_pad_clearance_label, "fiducial_pad_clearance_label");
  gtk_widget_show (fiducial_pad_clearance_label);
  gtk_table_attach (GTK_TABLE (fiducials_table), fiducial_pad_clearance_label, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (fiducial_pad_clearance_label), 0, 0.5);

  fiducial_pad_clearance_entry = gtk_entry_new ();
  gtk_widget_set_name (fiducial_pad_clearance_entry, "fiducial_pad_clearance_entry");
  gtk_widget_show (fiducial_pad_clearance_entry);
  gtk_table_attach (GTK_TABLE (fiducials_table), fiducial_pad_clearance_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, fiducial_pad_clearance_entry, _("Clearance distance with polygons"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (fiducial_pad_clearance_entry), 8226);

  fiducials_label = gtk_label_new (_("<b>Fiducials</b>"));
  gtk_widget_set_name (fiducials_label, "fiducials_label");
  gtk_widget_show (fiducials_label);
  gtk_frame_set_label_widget (GTK_FRAME (fiducials_frame), fiducials_label);
  gtk_label_set_use_markup (GTK_LABEL (fiducials_label), TRUE);

  thermal_pad_tab_label = gtk_label_new (_("Thermal pad"));
  gtk_widget_set_name (thermal_pad_tab_label, "thermal_pad_tab_label");
  gtk_widget_show (thermal_pad_tab_label);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 3), thermal_pad_tab_label);

  heel_and_toe_goals_vbox = gtk_vbox_new (FALSE, 10);
  gtk_widget_set_name (heel_and_toe_goals_vbox, "heel_and_toe_goals_vbox");
  gtk_widget_show (heel_and_toe_goals_vbox);
  gtk_container_add (GTK_CONTAINER (notebook), heel_and_toe_goals_vbox);

  top_to_bottom_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (top_to_bottom_frame, "top_to_bottom_frame");
  gtk_widget_show (top_to_bottom_frame);
  gtk_box_pack_start (GTK_BOX (heel_and_toe_goals_vbox), top_to_bottom_frame, FALSE, TRUE, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (top_to_bottom_frame), GTK_SHADOW_NONE);

  top_to_bottom_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (top_to_bottom_alignment, "top_to_bottom_alignment");
  gtk_widget_show (top_to_bottom_alignment);
  gtk_container_add (GTK_CONTAINER (top_to_bottom_frame), top_to_bottom_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (top_to_bottom_alignment), 0, 0, 12, 0);

  top_to_bottom_table = gtk_table_new (3, 2, FALSE);
  gtk_widget_set_name (top_to_bottom_table, "top_to_bottom_table");
  gtk_widget_show (top_to_bottom_table);
  gtk_container_add (GTK_CONTAINER (top_to_bottom_alignment), top_to_bottom_table);

  G1_radiobutton = gtk_radio_button_new_with_mnemonic (NULL, _("Inner-Inner (G1)"));
  gtk_widget_set_name (G1_radiobutton, "G1_radiobutton");
  gtk_widget_show (G1_radiobutton);
  gtk_table_attach (GTK_TABLE (top_to_bottom_table), G1_radiobutton, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (G1_radiobutton), G1_radiobutton_group);
  G1_radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (G1_radiobutton));

  C1_radiobutton = gtk_radio_button_new_with_mnemonic (NULL, _("Center-Center (C1)"));
  gtk_widget_set_name (C1_radiobutton, "C1_radiobutton");
  gtk_widget_show (C1_radiobutton);
  gtk_table_attach (GTK_TABLE (top_to_bottom_table), C1_radiobutton, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (C1_radiobutton), G1_radiobutton_group);
  G1_radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (C1_radiobutton));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C1_radiobutton), TRUE);

  Z1_radiobutton = gtk_radio_button_new_with_mnemonic (NULL, _("Outer-Outer (Z1)"));
  gtk_widget_set_name (Z1_radiobutton, "Z1_radiobutton");
  gtk_widget_show (Z1_radiobutton);
  gtk_table_attach (GTK_TABLE (top_to_bottom_table), Z1_radiobutton, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (Z1_radiobutton), G1_radiobutton_group);
  G1_radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (Z1_radiobutton));

  G1_entry = gtk_entry_new ();
  gtk_widget_set_name (G1_entry, "G1_entry");
  gtk_widget_show (G1_entry);
  gtk_table_attach (GTK_TABLE (top_to_bottom_table), G1_entry, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, G1_entry, _("Top to bottom inner distance between pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (G1_entry), 8226);

  C1_entry = gtk_entry_new ();
  gtk_widget_set_name (C1_entry, "C1_entry");
  gtk_widget_show (C1_entry);
  gtk_table_attach (GTK_TABLE (top_to_bottom_table), C1_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, C1_entry, _("Top to bottom center distance between pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (C1_entry), 8226);

  Z1_entry = gtk_entry_new ();
  gtk_widget_set_name (Z1_entry, "Z1_entry");
  gtk_widget_show (Z1_entry);
  gtk_table_attach (GTK_TABLE (top_to_bottom_table), Z1_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, Z1_entry, _("Top to bottom outer distance between pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (Z1_entry), 8226);

  top_to_bottom_label = gtk_label_new (_("<b>Top to Bottom</b>"));
  gtk_widget_set_name (top_to_bottom_label, "top_to_bottom_label");
  gtk_widget_show (top_to_bottom_label);
  gtk_frame_set_label_widget (GTK_FRAME (top_to_bottom_frame), top_to_bottom_label);
  gtk_label_set_use_markup (GTK_LABEL (top_to_bottom_label), TRUE);

  left_to_right_frame = gtk_frame_new (NULL);
  gtk_widget_set_name (left_to_right_frame, "left_to_right_frame");
  gtk_widget_show (left_to_right_frame);
  gtk_box_pack_start (GTK_BOX (heel_and_toe_goals_vbox), left_to_right_frame, FALSE, TRUE, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (left_to_right_frame), GTK_SHADOW_NONE);

  left_to_right_alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_set_name (left_to_right_alignment, "left_to_right_alignment");
  gtk_widget_show (left_to_right_alignment);
  gtk_container_add (GTK_CONTAINER (left_to_right_frame), left_to_right_alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (left_to_right_alignment), 0, 0, 12, 0);

  left_to_right_table = gtk_table_new (3, 2, FALSE);
  gtk_widget_set_name (left_to_right_table, "left_to_right_table");
  gtk_widget_show (left_to_right_table);
  gtk_container_add (GTK_CONTAINER (left_to_right_alignment), left_to_right_table);

  G2_radiobutton = gtk_radio_button_new_with_mnemonic (NULL, _("Inner-Inner (G2)"));
  gtk_widget_set_name (G2_radiobutton, "G2_radiobutton");
  gtk_widget_show (G2_radiobutton);
  gtk_table_attach (GTK_TABLE (left_to_right_table), G2_radiobutton, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (G2_radiobutton), G2_radiobutton_group);
  G2_radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (G2_radiobutton));

  C2_radiobutton = gtk_radio_button_new_with_mnemonic (NULL, _("Center-Center (C2)"));
  gtk_widget_set_name (C2_radiobutton, "C2_radiobutton");
  gtk_widget_show (C2_radiobutton);
  gtk_table_attach (GTK_TABLE (left_to_right_table), C2_radiobutton, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (C2_radiobutton), G2_radiobutton_group);
  G2_radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (C2_radiobutton));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C2_radiobutton), TRUE);

  Z2_radiobutton = gtk_radio_button_new_with_mnemonic (NULL, _("Outer-Outer (Z2)"));
  gtk_widget_set_name (Z2_radiobutton, "Z2_radiobutton");
  gtk_widget_show (Z2_radiobutton);
  gtk_table_attach (GTK_TABLE (left_to_right_table), Z2_radiobutton, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_radio_button_set_group (GTK_RADIO_BUTTON (Z2_radiobutton), G2_radiobutton_group);
  G2_radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (Z2_radiobutton));

  G2_entry = gtk_entry_new ();
  gtk_widget_set_name (G2_entry, "G2_entry");
  gtk_widget_show (G2_entry);
  gtk_table_attach (GTK_TABLE (left_to_right_table), G2_entry, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, G2_entry, _("Left to right inner distance between pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (G2_entry), 8226);

  C2_entry = gtk_entry_new ();
  gtk_widget_set_name (C2_entry, "C2_entry");
  gtk_widget_show (C2_entry);
  gtk_table_attach (GTK_TABLE (left_to_right_table), C2_entry, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, C2_entry, _("Left to right center distance between pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (C2_entry), 8226);

  Z2_entry = gtk_entry_new ();
  gtk_widget_set_name (Z2_entry, "Z2_entry");
  gtk_widget_show (Z2_entry);
  gtk_table_attach (GTK_TABLE (left_to_right_table), Z2_entry, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, Z2_entry, _("Left to right outer distance between pads"), NULL);
  gtk_entry_set_invisible_char (GTK_ENTRY (Z2_entry), 8226);

  left_to_right_label = gtk_label_new (_("<b>Left to Right</b>"));
  gtk_widget_set_name (left_to_right_label, "left_to_right_label");
  gtk_widget_show (left_to_right_label);
  gtk_frame_set_label_widget (GTK_FRAME (left_to_right_frame), left_to_right_label);
  gtk_label_set_use_markup (GTK_LABEL (left_to_right_label), TRUE);

  heel_and_toe_goals_tab_label = gtk_label_new (_("Heel & Toe goals"));
  gtk_widget_set_name (heel_and_toe_goals_tab_label, "heel_and_toe_goals_tab_label");
  gtk_widget_show (heel_and_toe_goals_tab_label);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 4), heel_and_toe_goals_tab_label);

  hbuttonbox0 = gtk_hbutton_box_new ();
  gtk_widget_set_name (hbuttonbox0, "hbuttonbox0");
  gtk_widget_show (hbuttonbox0);
  gtk_box_pack_start (GTK_BOX (vbox), hbuttonbox0, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbuttonbox0), 10);

  refresh_button = gtk_button_new_from_stock ("gtk-refresh");
  gtk_widget_set_name (refresh_button, "refresh_button");
  gtk_widget_show (refresh_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox0), refresh_button);
  GTK_WIDGET_SET_FLAGS (refresh_button, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, refresh_button, _("Click on the refresh button to refresh the preview"), NULL);

  dimensions_button = gtk_button_new ();
  gtk_widget_set_name (dimensions_button, "dimensions_button");
  gtk_widget_show (dimensions_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox0), dimensions_button);
  GTK_WIDGET_SET_FLAGS (dimensions_button, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, dimensions_button, _("Click on the Dimensions button for the package dimensions"), NULL);

  alignment4 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_set_name (alignment4, "alignment4");
  gtk_widget_show (alignment4);
  gtk_container_add (GTK_CONTAINER (dimensions_button), alignment4);

  hbox4 = gtk_hbox_new (FALSE, 2);
  gtk_widget_set_name (hbox4, "hbox4");
  gtk_widget_show (hbox4);
  gtk_container_add (GTK_CONTAINER (alignment4), hbox4);

  image4 = gtk_image_new_from_stock ("gtk-info", GTK_ICON_SIZE_BUTTON);
  gtk_widget_set_name (image4, "image4");
  gtk_widget_show (image4);
  gtk_box_pack_start (GTK_BOX (hbox4), image4, FALSE, FALSE, 0);

  label6 = gtk_label_new_with_mnemonic (_("Dimensions"));
  gtk_widget_set_name (label6, "label6");
  gtk_widget_show (label6);
  gtk_box_pack_start (GTK_BOX (hbox4), label6, FALSE, FALSE, 0);

  preview_button = gtk_button_new ();
  gtk_widget_set_name (preview_button, "preview_button");
  gtk_widget_show (preview_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox0), preview_button);
  GTK_WIDGET_SET_FLAGS (preview_button, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, preview_button, _("Click on the Preview button to view the footprint"), NULL);

  alignment1 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_set_name (alignment1, "alignment1");
  gtk_widget_show (alignment1);
  gtk_container_add (GTK_CONTAINER (preview_button), alignment1);

  hbox1 = gtk_hbox_new (FALSE, 2);
  gtk_widget_set_name (hbox1, "hbox1");
  gtk_widget_show (hbox1);
  gtk_container_add (GTK_CONTAINER (alignment1), hbox1);

  image1 = gtk_image_new_from_stock ("gtk-zoom-fit", GTK_ICON_SIZE_BUTTON);
  gtk_widget_set_name (image1, "image1");
  gtk_widget_show (image1);
  gtk_box_pack_start (GTK_BOX (hbox1), image1, FALSE, FALSE, 0);

  label3 = gtk_label_new_with_mnemonic (_("Preview"));
  gtk_widget_set_name (label3, "label3");
  gtk_widget_show (label3);
  gtk_box_pack_start (GTK_BOX (hbox1), label3, FALSE, FALSE, 0);

  clear_button = gtk_button_new_from_stock ("gtk-clear");
  gtk_widget_set_name (clear_button, "clear_button");
  gtk_widget_show (clear_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox0), clear_button);
  GTK_WIDGET_SET_FLAGS (clear_button, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, clear_button, _("Click on the Clear button to clear all entries"), NULL);

  hbuttonbox1 = gtk_hbutton_box_new ();
  gtk_widget_set_name (hbuttonbox1, "hbuttonbox1");
  gtk_widget_show (hbuttonbox1);
  gtk_box_pack_start (GTK_BOX (vbox), hbuttonbox1, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbuttonbox1), 10);

  close_button = gtk_button_new_from_stock ("gtk-close");
  gtk_widget_set_name (close_button, "close_button");
  gtk_widget_show (close_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), close_button);
  GTK_WIDGET_SET_FLAGS (close_button, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, close_button, _("Click the Close button to exit"), NULL);

  footprint_button = gtk_button_new ();
  gtk_widget_set_name (footprint_button, "footprint_button");
  gtk_widget_show (footprint_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), footprint_button);
  GTK_WIDGET_SET_FLAGS (footprint_button, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, footprint_button, _("Click the Footprint button to write a footprint file"), NULL);

  alignment3 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_set_name (alignment3, "alignment3");
  gtk_widget_show (alignment3);
  gtk_container_add (GTK_CONTAINER (footprint_button), alignment3);

  hbox3 = gtk_hbox_new (FALSE, 2);
  gtk_widget_set_name (hbox3, "hbox3");
  gtk_widget_show (hbox3);
  gtk_container_add (GTK_CONTAINER (alignment3), hbox3);

  image3 = gtk_image_new_from_stock ("gtk-file", GTK_ICON_SIZE_BUTTON);
  gtk_widget_set_name (image3, "image3");
  gtk_widget_show (image3);
  gtk_box_pack_start (GTK_BOX (hbox3), image3, FALSE, FALSE, 0);

  label5 = gtk_label_new_with_mnemonic ("Footprint");
  gtk_widget_set_name (label5, "label5");
  gtk_widget_show (label5);
  gtk_box_pack_start (GTK_BOX (hbox3), label5, FALSE, FALSE, 0);

  open_button = gtk_button_new_from_stock ("gtk-open");
  gtk_widget_set_name (open_button, "open_button");
  gtk_widget_show (open_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), open_button);
  GTK_WIDGET_SET_FLAGS (open_button, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, open_button, _("Click the Open button to read an existing footprint file"), NULL);

  save_button = gtk_button_new_from_stock ("gtk-save");
  gtk_widget_set_name (save_button, "save_button");
  gtk_widget_show (save_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), save_button);
  GTK_WIDGET_SET_FLAGS (save_button, GTK_CAN_DEFAULT);
  gtk_tooltips_set_tip (tooltips, save_button, _("Click the Save button to write the footprintwizard file"), NULL);

  statusbar = gtk_statusbar_new ();
  gtk_widget_set_name (statusbar, "statusbar");
  gtk_widget_show (statusbar);
  gtk_box_pack_start (GTK_BOX (vbox), statusbar, FALSE, FALSE, 0);

  g_signal_connect ((gpointer) pcb_gfpw, "destroy",
                    G_CALLBACK (on_pcb_gfpw_destroy),
                    NULL);
  g_signal_connect ((gpointer) footprint_author_entry, "changed",
                    G_CALLBACK (on_footprint_author_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) footprint_dist_license_entry, "changed",
                    G_CALLBACK (on_footprint_dist_license_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) footprint_use_license_entry, "changed",
                    G_CALLBACK (on_footprint_use_license_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) footprint_status_entry, "changed",
                    G_CALLBACK (on_footprint_status_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) footprint_units_entry, "changed",
                    G_CALLBACK (on_footprint_units_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) footprint_name_entry, "changed",
                    G_CALLBACK (on_footprint_name_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) footprint_type_entry, "changed",
                    G_CALLBACK (on_footprint_type_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) package_body_height_entry, "changed",
                    G_CALLBACK (on_package_body_height_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) package_body_width_entry, "changed",
                    G_CALLBACK (on_package_body_width_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) package_body_length_entry, "changed",
                    G_CALLBACK (on_package_body_length_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) footprint_value_entry, "changed",
                    G_CALLBACK (on_footprint_value_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) footprint_refdes_entry, "changed",
                    G_CALLBACK (on_footprint_refdes_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) add_license_checkbutton, "toggled",
                    G_CALLBACK (on_add_license_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) package_is_radial_checkbutton, "toggled",
                    G_CALLBACK (on_package_is_radial_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) add_attribs_checkbutton, "toggled",
                    G_CALLBACK (on_add_attribs_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) pad_solder_mask_clearance_entry, "changed",
                    G_CALLBACK (on_pad_solder_mask_clearance_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pad_clearance_entry, "changed",
                    G_CALLBACK (on_pad_clearance_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pad_width_entry, "changed",
                    G_CALLBACK (on_pad_width_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pad_length_entry, "changed",
                    G_CALLBACK (on_pad_length_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pad_shape_entry, "changed",
                    G_CALLBACK (on_pad_shape_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pad_diameter_entry, "changed",
                    G_CALLBACK (on_pad_diameter_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pin_square_checkbutton, "toggled",
                    G_CALLBACK (on_pin_square_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) pin_drill_diameter_entry, "changed",
                    G_CALLBACK (on_pin_drill_diameter_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) number_total_pins_entry, "changed",
                    G_CALLBACK (on_number_total_pins_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pitch_x_entry, "changed",
                    G_CALLBACK (on_pitch_x_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pitch_y_entry, "changed",
                    G_CALLBACK (on_pitch_y_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) count_x_entry, "changed",
                    G_CALLBACK (on_count_x_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) count_y_entry, "changed",
                    G_CALLBACK (on_count_y_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) number_1_position_entry, "changed",
                    G_CALLBACK (on_number_1_position_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) number_of_columns_entry, "changed",
                    G_CALLBACK (on_number_of_columns_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) number_of_rows_entry, "changed",
                    G_CALLBACK (on_number_of_rows_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pin_pad_exceptions_entry, "changed",
                    G_CALLBACK (on_pin_pad_exceptions_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) pin_pad_exceptions_button, "clicked",
                    G_CALLBACK (on_pin_pad_exceptions_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) courtyard_checkbutton, "toggled",
                    G_CALLBACK (on_courtyard_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) courtyard_length_entry, "changed",
                    G_CALLBACK (on_courtyard_length_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) courtyard_width_entry, "changed",
                    G_CALLBACK (on_courtyard_width_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) courtyard_line_width_entry, "changed",
                    G_CALLBACK (on_courtyard_line_width_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) courtyard_clearance_with_package_entry, "changed",
                    G_CALLBACK (on_courtyard_clearance_with_package_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) silkscreen_package_outline_checkbutton, "toggled",
                    G_CALLBACK (on_silkscreen_package_outline_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) silkscreen_indicate_1_checkbutton, "toggled",
                    G_CALLBACK (on_silkscreen_indicate_1_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) silkscreen_line_width_entry, "changed",
                    G_CALLBACK (on_silkscreen_line_width_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) thermal_checkbutton, "toggled",
                    G_CALLBACK (on_thermal_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) thermal_width_entry, "changed",
                    G_CALLBACK (on_thermal_width_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) thermal_length_entry, "changed",
                    G_CALLBACK (on_thermal_length_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) thermal_nopaste_checkbutton, "toggled",
                    G_CALLBACK (on_thermal_nopaste_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) thermal_solder_mask_clearance_entry, "changed",
                    G_CALLBACK (on_thermal_solder_mask_clearance_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) thermal_clearance_entry, "changed",
                    G_CALLBACK (on_thermal_clearance_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) fiducial_pad_diameter_entry, "changed",
                    G_CALLBACK (on_fiducial_pad_diameter_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) fiducial_checkbutton, "toggled",
                    G_CALLBACK (on_fiducial_checkbutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) fiducial_pad_solder_mask_clearance_entry, "changed",
                    G_CALLBACK (on_fiducial_pad_solder_mask_clearance_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) fiducial_pad_clearance_entry, "changed",
                    G_CALLBACK (on_fiducial_pad_clearance_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) G1_radiobutton, "toggled",
                    G_CALLBACK (on_G1_radiobutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) C1_radiobutton, "toggled",
                    G_CALLBACK (on_C1_radiobutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) Z1_radiobutton, "toggled",
                    G_CALLBACK (on_Z1_radiobutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) G1_entry, "changed",
                    G_CALLBACK (on_G1_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) C1_entry, "changed",
                    G_CALLBACK (on_C1_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) Z1_entry, "changed",
                    G_CALLBACK (on_Z1_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) G2_radiobutton, "toggled",
                    G_CALLBACK (on_G2_radiobutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) C2_radiobutton, "toggled",
                    G_CALLBACK (on_C2_radiobutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) Z2_radiobutton, "toggled",
                    G_CALLBACK (on_Z2_radiobutton_toggled),
                    NULL);
  g_signal_connect ((gpointer) G2_entry, "changed",
                    G_CALLBACK (on_G2_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) C2_entry, "changed",
                    G_CALLBACK (on_C2_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) Z2_entry, "changed",
                    G_CALLBACK (on_Z2_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) refresh_button, "clicked",
                    G_CALLBACK (on_refresh_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) dimensions_button, "clicked",
                    G_CALLBACK (on_dimensions_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) preview_button, "clicked",
                    G_CALLBACK (on_preview_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) clear_button, "clicked",
                    G_CALLBACK (on_clear_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) close_button, "clicked",
                    G_CALLBACK (on_close_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) footprint_button, "clicked",
                    G_CALLBACK (on_footprint_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) open_button, "clicked",
                    G_CALLBACK (on_open_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) save_button, "clicked",
                    G_CALLBACK (on_save_button_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (pcb_gfpw, pcb_gfpw, "pcb_gfpw");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, vbox, "vbox");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, hbox, "hbox");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, notebook, "notebook");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_tab_table, "footprint_tab_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, author_frame, "author_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, author_frame_alignment, "author_frame_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, author_table, "author_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_author_label, "footprint_author_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_dist_license_label, "footprint_dist_license_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_author_entry, "footprint_author_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_dist_license_entry, "footprint_dist_license_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_use_license_entry, "footprint_use_license_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_use_license_label, "footprint_use_license_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_status_label, "footprint_status_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_status_entry, "footprint_status_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, author_frame_label, "author_frame_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_frame, "footprint_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_frame_alignment, "footprint_frame_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_table, "footprint_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_units_label, "footprint_units_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_units_entry, "footprint_units_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_name_entry, "footprint_name_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_type_entry, "footprint_type_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_type_label, "footprint_type_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_name_label, "footprint_name_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_body_height_entry, "package_body_height_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_body_height_label, "package_body_height_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pacakge_body_width_label, "pacakge_body_width_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_body_length_label, "package_body_length_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_value_label, "footprint_value_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_body_width_entry, "package_body_width_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_body_length_entry, "package_body_length_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_value_entry, "footprint_value_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_refdes_label, "footprint_refdes_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_refdes_entry, "footprint_refdes_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, add_license_checkbutton, "add_license_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_is_radial_checkbutton, "package_is_radial_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, add_attribs_checkbutton, "add_attribs_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_frame_label, "footprint_frame_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_tab_label, "footprint_tab_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_pads_table, "pins_pads_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pads_frame, "pads_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pads_alignment, "pads_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pads_table, "pads_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_solder_mask_clearance_label, "pad_solder_mask_clearance_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_solder_mask_clearance_entry, "pad_solder_mask_clearance_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_clearance_label, "pad_clearance_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_width_label, "pad_width_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_length_label, "pad_length_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_clearance_entry, "pad_clearance_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_width_entry, "pad_width_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_length_entry, "pad_length_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_shape_label, "pad_shape_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_shape_entry, "pad_shape_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pads_label, "pads_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_frame, "pins_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_alignment, "pins_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_table, "pins_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pad_diameter_entry, "pad_diameter_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pin_drill_diameter_label, "pin_drill_diameter_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pin_pad_diameter_label, "pin_pad_diameter_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pin_square_checkbutton, "pin_square_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pin_drill_diameter_entry, "pin_drill_diameter_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_label, "pins_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_pads_pattern_frame, "pins_pads_pattern_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_pads_pattern_alignment, "pins_pads_pattern_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_pads_pattern_table, "pins_pads_pattern_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, total_pins_and_pads_label, "total_pins_and_pads_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pitch_x_label, "pitch_x_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pitch_y_label, "pitch_y_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, number_total_pins_entry, "number_total_pins_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pitch_x_entry, "pitch_x_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pitch_y_entry, "pitch_y_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, label1, "label1");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, label2, "label2");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, count_x_entry, "count_x_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, count_y_entry, "count_y_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, number_1_position_label, "number_1_position_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, number_1_position_entry, "number_1_position_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, number_of_columns_label, "number_of_columns_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, number_of_columns_entry, "number_of_columns_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, number_of_rows_label, "number_of_rows_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, number_of_rows_entry, "number_of_rows_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pin_pad_exceptions_entry, "pin_pad_exceptions_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pin_pad_exceptions_button, "pin_pad_exceptions_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_pads_pattern_label, "pins_pads_pattern_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, pins_pads_tab_tab_label, "pins_pads_tab_tab_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, silkscreen_table, "silkscreen_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_frame, "courtyard_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_alignment, "courtyard_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_table, "courtyard_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_checkbutton, "courtyard_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_width_label, "courtyard_width_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_length_label, "courtyard_length_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_length_entry, "courtyard_length_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_width_entry, "courtyard_width_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_line_width_label, "courtyard_line_width_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_line_width_entry, "courtyard_line_width_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_clearance_with_package_label, "courtyard_clearance_with_package_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_clearance_with_package_entry, "courtyard_clearance_with_package_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, courtyard_label, "courtyard_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_frame, "package_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_alignment, "package_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_table, "package_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, silkscreen_package_outline_checkbutton, "silkscreen_package_outline_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, silkscreen_indicate_1_checkbutton, "silkscreen_indicate_1_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, silkscreen_line_width_label, "silkscreen_line_width_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, silkscreen_line_width_entry, "silkscreen_line_width_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, package_label, "package_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, silkscreen_tab_label, "silkscreen_tab_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_table, "thermal_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_frame, "thermal_pad_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_alignment, "thermal_pad_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_table, "thermal_pad_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_checkbutton, "thermal_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_length_label, "thermal_pad_length_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_width_label, "thermal_pad_width_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_width_entry, "thermal_width_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_length_entry, "thermal_length_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_nopaste_checkbutton, "thermal_nopaste_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_solder_mask_clearance_label, "thermal_pad_solder_mask_clearance_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_clearance_label, "thermal_pad_clearance_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_solder_mask_clearance_entry, "thermal_solder_mask_clearance_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_clearance_entry, "thermal_clearance_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_label, "thermal_pad_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducials_frame, "fiducials_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducials_alignment, "fiducials_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducials_table, "fiducials_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducial_pad_diameter_label, "fiducial_pad_diameter_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducial_pad_diameter_entry, "fiducial_pad_diameter_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducial_checkbutton, "fiducial_checkbutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducial_solder_mask_clearance_label, "fiducial_solder_mask_clearance_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducial_pad_solder_mask_clearance_entry, "fiducial_pad_solder_mask_clearance_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducial_pad_clearance_label, "fiducial_pad_clearance_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducial_pad_clearance_entry, "fiducial_pad_clearance_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, fiducials_label, "fiducials_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, thermal_pad_tab_label, "thermal_pad_tab_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, heel_and_toe_goals_vbox, "heel_and_toe_goals_vbox");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, top_to_bottom_frame, "top_to_bottom_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, top_to_bottom_alignment, "top_to_bottom_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, top_to_bottom_table, "top_to_bottom_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, G1_radiobutton, "G1_radiobutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, C1_radiobutton, "C1_radiobutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, Z1_radiobutton, "Z1_radiobutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, G1_entry, "G1_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, C1_entry, "C1_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, Z1_entry, "Z1_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, top_to_bottom_label, "top_to_bottom_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, left_to_right_frame, "left_to_right_frame");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, left_to_right_alignment, "left_to_right_alignment");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, left_to_right_table, "left_to_right_table");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, G2_radiobutton, "G2_radiobutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, C2_radiobutton, "C2_radiobutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, Z2_radiobutton, "Z2_radiobutton");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, G2_entry, "G2_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, C2_entry, "C2_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, Z2_entry, "Z2_entry");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, left_to_right_label, "left_to_right_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, heel_and_toe_goals_tab_label, "heel_and_toe_goals_tab_label");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, hbuttonbox0, "hbuttonbox0");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, refresh_button, "refresh_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, dimensions_button, "dimensions_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, alignment4, "alignment4");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, image4, "image4");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, label6, "label6");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, preview_button, "preview_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, alignment1, "alignment1");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, image1, "image1");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, label3, "label3");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, clear_button, "clear_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, hbuttonbox1, "hbuttonbox1");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, close_button, "close_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, footprint_button, "footprint_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, alignment3, "alignment3");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, image3, "image3");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, label5, "label5");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, open_button, "open_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, save_button, "save_button");
  GLADE_HOOKUP_OBJECT (pcb_gfpw, statusbar, "statusbar");
  GLADE_HOOKUP_OBJECT_NO_REF (pcb_gfpw, tooltips, "tooltips");

  return pcb_gfpw;
}

GtkWidget*
create_filechooser_dialog (void)
{
  GtkWidget *filechooser_dialog;
  GdkPixbuf *filechooser_dialog_icon_pixbuf;
  GtkWidget *filechooser_dialog_vbox;
  GtkWidget *filechooser_dialog_action_area;
  GtkWidget *filechooser_dialog_cancel_button;
  GtkWidget *filechooser_dialog_open_button;

  filechooser_dialog = gtk_file_chooser_dialog_new (_("pcb-gfpw: choose a .fpw file"), NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL);
  gtk_widget_set_name (filechooser_dialog, "filechooser_dialog");
  filechooser_dialog_icon_pixbuf = create_pixbuf ("gFootprintWizard.xpm");
  if (filechooser_dialog_icon_pixbuf)
    {
      gtk_window_set_icon (GTK_WINDOW (filechooser_dialog), filechooser_dialog_icon_pixbuf);
      gdk_pixbuf_unref (filechooser_dialog_icon_pixbuf);
    }
  gtk_window_set_type_hint (GTK_WINDOW (filechooser_dialog), GDK_WINDOW_TYPE_HINT_DIALOG);

  filechooser_dialog_vbox = GTK_DIALOG (filechooser_dialog)->vbox;
  gtk_widget_set_name (filechooser_dialog_vbox, "filechooser_dialog_vbox");
  gtk_widget_show (filechooser_dialog_vbox);

  filechooser_dialog_action_area = GTK_DIALOG (filechooser_dialog)->action_area;
  gtk_widget_set_name (filechooser_dialog_action_area, "filechooser_dialog_action_area");
  gtk_widget_show (filechooser_dialog_action_area);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (filechooser_dialog_action_area), GTK_BUTTONBOX_END);

  filechooser_dialog_cancel_button = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_set_name (filechooser_dialog_cancel_button, "filechooser_dialog_cancel_button");
  gtk_widget_show (filechooser_dialog_cancel_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (filechooser_dialog), filechooser_dialog_cancel_button, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (filechooser_dialog_cancel_button, GTK_CAN_DEFAULT);

  filechooser_dialog_open_button = gtk_button_new_from_stock ("gtk-open");
  gtk_widget_set_name (filechooser_dialog_open_button, "filechooser_dialog_open_button");
  gtk_widget_show (filechooser_dialog_open_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (filechooser_dialog), filechooser_dialog_open_button, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (filechooser_dialog_open_button, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) filechooser_dialog, "selection_changed",
                    G_CALLBACK (on_filechooser_dialog_selection_changed),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog, "close",
                    G_CALLBACK (on_filechooser_dialog_close),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog, "current_folder_changed",
                    G_CALLBACK (on_filechooser_dialog_current_folder_changed),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog, "update_preview",
                    G_CALLBACK (on_filechooser_dialog_update_preview),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog_cancel_button, "clicked",
                    G_CALLBACK (on_filechooser_dialog_cancel_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog_open_button, "clicked",
                    G_CALLBACK (on_filechooser_dialog_open_button_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (filechooser_dialog, filechooser_dialog, "filechooser_dialog");
  GLADE_HOOKUP_OBJECT_NO_REF (filechooser_dialog, filechooser_dialog_vbox, "filechooser_dialog_vbox");
  GLADE_HOOKUP_OBJECT_NO_REF (filechooser_dialog, filechooser_dialog_action_area, "filechooser_dialog_action_area");
  GLADE_HOOKUP_OBJECT (filechooser_dialog, filechooser_dialog_cancel_button, "filechooser_dialog_cancel_button");
  GLADE_HOOKUP_OBJECT (filechooser_dialog, filechooser_dialog_open_button, "filechooser_dialog_open_button");

  gtk_widget_grab_default (filechooser_dialog_open_button);
  return filechooser_dialog;
}


/* EOF */
