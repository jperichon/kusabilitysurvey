##Project background

This framework has been developed during the Google Summer of Code 2011, for KDE.
It allows designers to collect information about user’s experiences and usability problems with software by attaching small surveys to events or services.

The development is in C++ and respects the KDE's library code policies
(especially it implements Shared D-Pointers
 http://techbase.kde.org/Policies/Library_Code_Policy/Shared_D-Pointer_Example).

It requires both KDE and Boost libraries.

##What has been done?

- Parsing and generating CSV files.
- Management of the objects related to the survey and to the different types of questions

##What needs to be done?

The main thing left to do is to port the previous version of the notification survey at git://anongit.kde.org/notificationsurvey to this framework. 
