# Torpedo-Arduino
A simple retro torpedo catching arduino game.
All you need is 3 buttons and an OLED display.

![DSC_0208](https://user-images.githubusercontent.com/35427514/104076792-c9eabc80-521f-11eb-82ad-161690a12c68.JPG)

This repo contains two versions of this game. One for SSD1306 and one for SH1106 display chips. 0.96" OLED display will most likely contain SSD1306 and 1.3" will have SH1106 chip.

This game is tested only on 128x64 displays, but the code is made flexible, so you can make it work with other resolutions just by editing the display initialization.

There is a commented option of adding gradually faster 1st level. By uncommenting, you will make lvl-1 much slower at the beginning.

![Torpedo](https://user-images.githubusercontent.com/35427514/104076600-374a1d80-521f-11eb-8158-39c1d88654b9.png)
