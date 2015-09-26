You can now visit our development blog at http://vexxdev.blogspot.com/ where we will be talking about the work going into Synapse and other projects as it happens.

Update 28 February 2011: After being featured on a few open source blogs and forums we have had a lot of traffic, and feedback. Thank you everyone for issues and contact feedback, we are trying to fix issues on the Synapse_1x branch to get a stable release which is usable.

Synapse currently depends on OpenGL to render images (something we plan to address in the next major release by adding a fallback CPU renderer), and we are receiving reports of the application not working on certain graphics hardware (although it has been tested on most major manufacturers hardware). We are working as hard as possible to resolve any issues we can soon. In the mean time, please bear with us!

Thanks to everyone who is giving Synapse a try.

Synapse is an open source Node Based compositor.

Please see our introduction and tour videos:

    Introduction Part 1
    Introduction Part 2 

    Properties Tour
    Viewer Tour
    Rotoscoping Tour
    Custom Nodes (GLSL)
    Custom Nodes (Macro) 

Feel free to go to our downloads page to get the latest version, or you can get the source code from the source tab!

Thanks to BitRocks cross platform installers, we now have a windows installer, other platforms are on their way!

There are currently a few bugs related to running Synapse on Linux, these bugs come from the current NVIDIA driver. If debug messages including convertFromLocalReferences() appear on the terminal you are being affected by these bugs. Rolling back or updating your driver may fix the problem. 
