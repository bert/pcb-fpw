#!/bin/sh
echo '<title>PCB-FPW: PCB FPW - Printed Circuit Board FootPrintWizard.</title>' > header.html
echo '<link href="doxygen.css" rel="stylesheet" type="text/css">' >> header.html
echo '<link href="tabs.css" rel="stylesheet" type="text/css">' >> header.html
echo '</head><body>' >> header.html
echo '<h3>PCB-FPW developer documentation based on version: ' $(git describe) ' </h3>' >> header.html
doxygen pcb-fpw.dox
echo 'Created doxygen documentation for pcb-fpw ...'

