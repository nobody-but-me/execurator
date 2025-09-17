
# Carol project

Carol is meant to be an all-in-one single-binary static website generator for Razomentalist, my new project of personal website. This is an experimental project for learning purposes -- i.e.: it's not meant to be finished or well-coded in any way. If it comes to become a real application, then this README will be, for sure, changed.

## How does it work?

Carol generates HTML files from *Radown* files and renders the generated HTML files in its own client and server sistem. Pretty simple.

## Radown

Radown is the "language" used by Carol to generate the HTML files. It is inspired by Markdown markup language and, just like Carol's whole system, it's pretty simple and straightforward:

```

[header] That's a header! [header]

[para] That's a paragraph! [para]

[link=https://asgooffeeasme.neocities.org] And that's a link! [link]

[image]https://raw.githubusercontent.com/nobody-but-me/MoL25/main/engine/assets/m.png[image]

```

## Building

```bash

 > sh build.sh

```

And follow the instructions. So then, open the local address http://localhost:4242 in your browser.

## TODO list

 ###### Features
 - [x] Load and parse Markdown-like files;
 - [x] Translate Radown files into HTML language;
 - [x] Load multiple Radown files from project folder;
 - [x] *Radown*: more simple "tags", like images and links;
 - [ ] *Radown* : Capacity to read nested tags;
 - [x] Multiple paging support;
 - [ ] ;
 ###### Structure
 - [x] Switch from shell scripts to Cmake;
 - [ ] Write a better README file;
 - [ ] ;


