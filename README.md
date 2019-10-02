# Tasks

A simple Qt application for viewing and managing tasks stored in plain text format.  
![tasks screenshot](https://k60.in/tasks.png)

## Design
Core logic is described within the `Task` class through mostly private methods.

Every task contains its title, creation date and status. Status can be either `DONE` or `TODO`. Tasks are stored as tab (actually, 4 spaces) separated values in `.txt` files, as such:
```
// title                         timestamp     status
This is an exmaple task title    1570037199    DONE
```

## Interface
Most of the applications' functions reside in its menus:  
![tasks menus](https://k60.in/tasks-menus.png)

The application supports some well-known keyboard shortcuts and conventions.
