OFPiWorkshop
============

Samples and Examples from the OF on RPi Workshop.

## The Examples

### osc_skeleton
This application is the base of all the others. It does nothing more than set up the basics for broadcasting and receiving osc messages.

### osc_audio_example
This one builds on the osc_skeleton, adding an audio play that reacts to mouse/moved and mouse/pressed messages from other clients on the network.

### osc_video_example
Here we give a simple example of modifying camera input data using osc messages.

### osc_graphics_example
In this example, we use the mouse/moved message and draw the remote mice locations on our own screen.

### osc_chatroom_example
A slightly more advanced example, this one builds a basic chatroom that will display chat messages sent from all other clients on the network.
NOTE: this one doesn't currently work on the Pi due to it's dependency on ofxUI addon.