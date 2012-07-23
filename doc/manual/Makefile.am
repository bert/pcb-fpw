# Makefile.am for autogenerating a User Manual.

EXTRA_DIST = \
	pcb-fpw_user-manual.xml \
	about_dialog.png \
	credits_dialog.png \
	footprint_tab.png \
	heel_and_toe_goals_tab.png \
	license_dialog.png \
	pins_pads_tab.png \
	select_exception_dialog.png \
	silkscreen_tab.png \
	thermal_pad_tab.png \
	translations_dialog.png

user_manual:
	./create_user_manual.sh

.DEFAULT_GOAL : all

all: user_manual

clean:
	-rm -rf *.html *~


