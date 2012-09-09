##Project background

This framework has been developed during the Google Summer of Code 2011, for KDE.
It allows designers to collect information about user’s experiences and usability problems with software by attaching small surveys to events or services.

The development is in C++ and respects the KDE's library code policies
(especially it implements Shared D-Pointers
 http://techbase.kde.org/Policies/Library_Code_Policy/Shared_D-Pointer_Example).

It requires both KDE and Boost libraries.

##Questions templates

###General structure
```
Number, Text, [Description], Response type, AcceptableResp1 | ... | AcceptableRespN, Option1 | ... | OptionN
```

###Text
```
1, My text question, , Text, , [maxLength]
```

###Scale
```
1, My linear scale question, , Scale, M | N, [itemMin | itemMax]
```
```
1, My scale question with icons, Scale, http://.../icon1.png | ... | http://.../iconN.png, [itemMin, itemMax]
```

###Grid
```
1, My linear grid question, , Grid, M | N, item1 | ... | itemN
```
```
1, My grid question with icons, , Grid, http://.../icon1.png | ... | http://.../iconN.png, item1 | ... | itemN
```

###List
```
1, My list question, , List, item1 | ... | itemN,
```
```
1, My list question with icons, , List, http://.../icon1.png | ... | http://.../iconN.png
```

###Checkbox
```
1, My checkbox question, , Checkbox, item1 | ... | itemN, [nbMaxItemsSelectable]
```
```
1, My checkbox question with icons, , Checkbox, http://.../icon1.png | ... | http://.../iconN.png, [nbMaxItemsSelectable]
```

###Radiobutton
```
1, My radiobutton question, , Radiobutton, item1 | ... | itemN,
```
```
1, My radiobutton question with icons, , Radiobutton, http://.../icon1.png | ... | http://.../iconN.png,
```
###Button
```
1, My button question, , Button, item1 | ... | itemN,
```
```
1, My button question with icons, , Button, http://.../icon1.png | ... | http://.../iconN.png,
```
###Like
```
1, My like question, , Like, ,
```

###Smiley scale
```
1, My smiley scale question, , SmileyScale, , [itemMin | itemMax]
```

###Smiley grid
```
1, My smiley grid, , SmileyGrid, , item1 | ... | itemN
```

##What has been done?

- Parsing and generating CSV files.
- Management of the objects related to the survey and to the different types of questions

##What needs to be done?

The main thing left to do is to port the previous version of the notification survey at git://anongit.kde.org/notificationsurvey to this framework. 