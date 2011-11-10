# NarGarTagetHem

This is a KDE plasmoid, which uses trafiklab.se in order to display realtime information of comuter train in Stockholm.
It shows if the trains are on time, and when they will go. If they are late, the plasmoid will turn red. If they are on time, it will be green.


I have hard coded Stockholms Central trains going south, and Rönninge with trains going north. So you would need to change it.

# To install

You need KDE 4.2

You need an API key from trafiklab.se, see 
http://www.trafiklab.se/kom-igang

In the file: narGarTagetHemPlasmoid.cpp
Change <YOU API KEY HERE> to your own API key.

``` C++
void narGarTagetHemPlasmoid::updateDeparture() {
  QString baseUrl = "https://api.trafiklab.se/sl/realtid/GetDpsDepartures.XML";
  QString key = "<YOU API KEY HERE>";
```


```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=`kde4-config --prefix` .. OR cmake -DCMAKE_INSTALL_PREFIX=$KDEDIRS .. 
make
sudo make install OR su -c "make install"
```
(your $KDEDIRS is where you install your KDE 4)

Restart plasma to load the applet 
```
kquitapp plasma
plasma
```

or view it with 
```
plasmoidviewer YourAppletName
```

You might need to run kbuildsycoca4 in order to get the .desktop file recognized.

# Tutorials and resources
The explanation of the template
http://techbase.kde.org/index.php?title=Development/Tutorials/Plasma/GettingStarted

Plasma techbase pages
http://techbase.kde.org/Projects/Plasma
