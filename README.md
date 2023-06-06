# Ballmer Linux kernel module

Are you a developer using Linux and you need a little bit of Ballmer inspiration? Now you can get this inspiration all day long, while your computer is running! Just compile and install this kernel module and run `cat /dev/ballmer` on the biggest screen in your home or office.

---

## Installation instructions

Clone the repository

```shell
$ git clone https://github.com/shinyvision/ballmer-linux.git
```

Change directory into the cloned repository

```shell
$ cd ballmer-linux
```

Build the module

```shell
$ make
```

Install the kernel module

```shell
$ sudo insmod ballmer.ko
```

And you're done!

## Usage

First, open a terminal or TTY on the biggest screen you own. Crank up the font size as big as you like and run the following command:

```shell
$ sudo cat /dev/ballmer
```

Now, sit back and feel yourself getting overwhelmed with inspiration and knowledge!

---

# In case it's not obvious, this is a joke.

If you didn't get it by now, I'm actually a little bit worried, but you should not worry. The module does work, it does what we expect, but it's not anything malicious. Feel free to play around with it, but when you're done, of course make sure to remove the module again, because it is very pointless.

```shell
$ sudo rmmod ballmer
```
