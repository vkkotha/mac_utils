## Mac Utils - swap_displays
Mac some times doesn't remeber the display positions after waking up from sleep.

This is a small Utility that swap Mac External display positions. This assumes the left display Id is smaller than rightDisplay Id. 

### Usage
#### Building
Run the command

```clang -o swap_displays -framework CoreGraphics swap_displays.c```

#### Installing 
Run the command 

```cp swap_displays /usr/local/bin```

#### Adding Mac Short Cut
##### Setup in Automator
- Open Mac ```Automator``` application
- Create new ```Quick Action```
- Select ```no input``` from Workflow receives in ```any application```
- Add ```Run Shell Script``` action
- Select /bin/zsh shell and add the command ```/usr/local/bin/swap_displays```
- Save the Action as ```Swap Displays```

##### Add Keyboard shortcut
- Open Mac ```System Settings```
- Click ```Keyboard```
- Click ```Keyboard Shortcuts...``` button
- Select ```Services```
- Open ```General``` You should see the Automator Action
- Double click on ```none```
- Enter desired short cut key combination.
- Click ```Done```