#!/bin/sh
echo '<title>PCB-FPW: PCB FPW - Printed Circuit Board FootPrintWizard.</title>' > header.html
echo '<link href="doxygen.css" rel="stylesheet" type="text/css">' >> header.html
echo '<link href="tabs.css" rel="stylesheet" type="text/css">' >> header.html
echo '</head><body>' >> header.html
echo '<table cellspacing="0" cellpadding="0">' >> header.html
echo ' <tbody>' >> header.html
echo ' <tr style="height: 48px;">' >> header.html
echo '  <td id="projectlogo"><img alt="Logo" src="pcb-fpw_48x48.png"></td>' >> header.html
echo '  <td style="padding-left: 0.5em;">' >> header.html
echo '   <div id="projectname">PCB-FPW<span id="projectnumber">' $(git describe) 'developer documentation.</span></div>' >> header.html
echo '  </td>' >> header.html
echo ' </tr>' >> header.html
echo ' </tbody>' >> header.html
echo '</table>' >> header.html
doxygen pcb-fpw.dox
echo 'Created doxygen documentation for pcb-fpw ...'

