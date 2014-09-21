jade
====

An experiment with something-or-other and other bits
----------------------------------------------------

I started making jade because Hey! Why not? and I wrote a bunch and it was silly and I still don't really know why it's all here but-

Jade is a thing that can do most things? Or, that is the eventual goal. Working on ubuntu 14.04, I wanted to figure out how it all works.

so I tried my hand at rewritting all the stuffs that you don't need to rewrite, making new arrays and vectors and linked lists so that I knnow in and out how they worked.
And then came other things, thiings that a thing that can do evverything needs. I looked into ALSA,the basic audio-thingy for linux, and played in it; I looked into X11 and XLib, the basic display-thingy for linux, and am playing in it.

And I just write what I think might be a good tool? And hopefully at some point I put a brain behind all of it, and that should be interesting.


My long term goal is: a program that you can tell to do something, and it will make an effort to do that thing.

Current abilities:

Input/Output
  * Listen to audio, record it, possibly maybe produce it but that is hard, audio files are annoying (Using [ALSA](http://www.alsa-project.org) and [libsnd](http://www.mega-nerd.com/libsndfile/)
  * Understand spoken words with [CMU Sphinx](http://cmusphinx.sourceforge.net/), which I haven't played enough with yet to like actually understand words correctly, but hopefully, hopefully
  * Also: speak words with [FestVox](http://festvox.org/), in a variety of voices
  * Webcam stuff with [OpenCV](http://docs.opencv.org/), and a lot of otherr stuff because OpenCV can do everything and is wonderful
  * Further image processing to detext barcodes and the like with [ZBar](bar.sourceforge.net/api/index.html)
  * Also: The [FaceTracker](https://github.com/kylemcdonald/FaceTracker) library by Kyle McDonald is incredibly cool, a little complicated, I wrote a rather thin wrapper to simplify things for myself
  * And also to do optical character recognition, which I'm not quite happy with yet, with [Leptonica](www.leptonica.org)
  * Internet connections and stuff are currently being used with [libCurl](http://curl.haxx.se/libcurl/)
  * Although sending emails is hard, I'm like really bad at it, so I just used the command line program [ESMTP](http://esmtp.sourceforge.net/) but-- it's weird.
  * Hopefully, soon, text messaging! By way of sending Emails. And recieving emails seems like something I should really add.
  * Getting input from the comuter itself with [XLib](http://www.x.org/releases/X11R7.6/doc/) (mouse position, keypresses, screenshots, and stuff), and making windows and drawing to those windows and making those windows funny shapes and moving the mouse automatically and automatically entering in keystrokes and more, maybe.
  * Also: outputting in color to the terminal, because the terminal needs colors.
  
Data Structures
  * I'm in the act of switching my data structures to more c++ type things from more c type things, but: I am trying to make a bunch of maps (linked list, arrays, tris, and more to come!) that are kind of interchangeable, with built in helpful functions like searching and I dunno, whatever? Lots of stuff, theoretically). 
  * Also, I might make some generic image and vector image types, topossibly simplify the fact that I have been dealing with OpenCV's Mats, OpenFramework's ofImage, XLib's XImage, Pixmap, and Bitmap and lots of strange things and everyone else's generic pointery guy.
  
And, other stuff! The tests folder is me just testing things as I make them, and snatches is just bits of code that I may use elsewhere, and then the things not in a folder are just kind of outliers.

The entire project is rather haphazard, but I find it interesting.
  

