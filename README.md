# Tasks

A simple Qt application for viewing and managing tasks stored in plain text format. Check out the included `example.txt` file to try it out.  
<img src="https://k60.in/tasks.png" width="469px" height="471px">

## Design
Core logic is described within the `Task` class through mostly private methods.

Every task contains its title, creation date and status. Status can be either `DONE` or `TODO`. Tasks are stored as tab (actually, 4 spaces) separated values in `.txt` files, as such:
```
// title                         timestamp     status
This is an exmaple task title    1570037199    DONE
```

## Interface
Most of the applications' functions reside in its menus:  
<img src="https://k60.in/tasks-menu.png" witdh="390" height="129">

The application supports some well-known keyboard shortcuts and conventions.
