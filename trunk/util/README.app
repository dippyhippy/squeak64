Welcome to Unix Squeak! (Mac OS X edition)


* Installing Squeak

Simply drag the Squeak application to your hard disk.

You will need '.image', '.changes' and '.sources' files before you can use Squeak.  If you don't already have these you can get them from

  ftp://ftp.squeakfoundation.org/official-dist

If you keep the '.sources' file (or a link to it) in the same directory as your image(s) you'll be fine.  Otherwise you can put it (or a link to it) in the 'Contents/MacOS' folder of the Squeak application.  You can also put the distributed '.image/.changes' files in the 'Contents/Resources' folder too (rename them to 'squeak.image' and 'squeak.changes'), if you want a convenient place from which to begin working in a fresh image.  More details are in the Squeak Help Book (which you can open from the "Help" menu in the running application).


* Starting Squeak

Squeak can be started either from the Finder (by double-clicking on the VM or an image file) or from the command line in a terminal window.  If it is started from the command line then various features (that are not available when launching it from the Finder) become available through command line options, such as running without a window (useful if the application is a Swiki or some other kind of server, for example).  (Some of these options will soon be available via a preferences panel in Quartz, when I get round to implementing it.)  A list of the available options is available by running Squeak from the command line and giving it the option '-help'.

If X11 is installed then display can be via X11 or via Quartz.  The default is X11 if the environment variable DISPLAY is set and Quartz if Squeak is launched from the Finder.  To force one or the other, Squeak can be run from the command line with the option '-vm-display-Quartz' or '-vm-display-X11' as desired.

Note that to run Squeak in a remote window the X11 libraries must be installed on the client machine, i.e., the one on which Squeak is running.


* Support

The Squeak home page contains useful information and links to various resources:

       <http://squeak.org>

The Unix Squeak home page has further information, source code, and the latest downloads specific to Unix and MacOSX:

	  <http://www-sor.inria.fr/~piumarta/squeak/>

If you have problems, questions, bugs to report, or specific feature requests concerning the Unix Squeak VM:

	<mailto:ian.piumarta@inria.fr>
