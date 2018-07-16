Ps3EYE_multicam_syphon_gui_osc
==============================


This app is depreciated and the repo will no longer be updated, please see https://github.com/fred-dev/ps3EyeSyphon_2 for the new version.


Input multiple ps3eye cameras and syphon out with osc control and gui.

press g to show the gui
click on the settings bar to access settings.
to go to the next camera press n
to go to the previous camera press p

The camera resolution framerate and the OSC input port are all set in the mySettings.xml file. You can edit these to valid settings in any text editor, then just save the file.

To control the cameras remotely send osc on the chosen port (default 1234) with the following structure.

/camera_number as int /setting

so to change the brightness on camera 2 to 0.5 send the following message address

/2/brighness with a float of 0.5

settings parameters and types are:
/camera_number/gain                        --float
/camera_number/shutter                    --float
/camera_number/brightness               --float
/camera_number/contrast                  --float
/camera_number/hue                         --float
/camera_number/flicker                      --int
/camera_number/white_balance        --int


All settings are saved when you click the save button in the gui, cameras will start up with the saved settings, including the draw setting.