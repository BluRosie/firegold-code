## Unown Report

![](/bpre-unown-report.gif)

The Johto-based games introduced an item called the [Unown Report](https://bulbapedia.bulbagarden.net/wiki/Unown_Report), which logs the Unown forms you have captured, and logs the player's research into the Ruins of Alph as they progress through the quest.

This ports that item to FR v1.0 ROMs using the CFRU build system with a few hacks.

### Build Instructions

Build the same as the CFRU:  `python scripts/make.py`

#### Cloning the repo

Open your terminal to whatever folder you want to download this repo into. Then, do the following to download the repo:

```shell
$ git clone https://github.com/BluRosie/firegold-code.git
$ cd firegold-code
```

Alternatively, you can download the code as a .zip file from the arrow above.  You can navigate to whichever branch for whichever feature you would like to check out as well.

#### Adding your ROM

Copy your ROM to this directory and rename it `BPRE0.gba`.

#### Configuration

##### Compile Time Constants

Open [scripts/make.py](https://github.com/BluRosie/firegold-code/blob/template/scripts/make.py#L12) in a text editor to set some compile-time configuration.

The build system is smart enough to find enough free space on its own, and if you want it to be inserted at a particular address, you can specify it by updating the definition of `OFFSET_TO_PUT`:

```python
OFFSET_TO_PUT = 0x1C88650
SEARCH_FREE_SPACE = True   # Set to True if you want the script to search for free space
                           # Set to False if you don't want to search for free space as you for example update the engine
```

The build system will use `OFFSET_TO_PUT` to determine where in the ROM it should start looking for free space if `SEARCH_FREE_SPACE` is `True`.  Otherwise, the build system places the code to insert directly at `OFFSET_TO_PUT`.

The code automatically sets the Field Script for the Unown Report to point to the correct function.

See the Usage section below for information on how the item should be configured.

##### Flags and Variables

This item requires two free variables, which are defined in the header files `include/constants/vars.h` and `include/constants/flags.h`, respectively.

This item interacts with the puzzles that are solved as well.  Successful completion of the puzzles unlocks a certain set of Unown letters that can appear in the wild.  The flags for puzzle completion are located in `include/constants/flags.h`

The two variables keep track of which Unown forms the player has captured.  Additional pages in the report are added as the player catches more forms.

#### Strings

If you want to edit the strings involved in this feature, they can be found and modified in `strings/unown_report.string`.

#### Building the project itself

Once you're ready, run:

```shell
$ python scripts/make.py
```

This won't actually modify `BPRE0.gba`, instead your output will be in `test.gba`. Naturally, test it in an emulator before continuing.

### Usage

#### How should I configure the Unown Report item?

As explained in the Compile Time Constants section above, running `python make.py` will automatically change the Field Script located at the offset in `routinepointers`.

The item requires some additional configuration to work as intended, however.

The `Pocket` should be `02 Key Items`. The `Type` should be `01 Out of battle`.

Of course, you can change the item's sprite and description at your leisure.

#### How can I change the background image?

Currently, the background is included directly as a raw byte array in `include/graphics/unown.c`.  This can either be changed here or after insertion using your favorite tool at your leisure.

### Caveats

* This code alters the move command `0xF1`, which is called by the battle system upon a Pokémon's capture to try and set the Pokédex flags. If your ROM hack has already changed this function, you may need to add your changes from vanilla to the `atkF1_TrySetCaughtMonDexFlags` function in `src/battle_script_commands.c`.

* This code also alters the function which registers the Pokédex flags of traded Pokémon, so if your hack has edited this function already, you will need to add your changes to the function `SetTradedMonPokedexFlags` in `src/trade.c`.

* At the moment, this code does not register new Unown forms obtained through `givepokemon`, Mystery Gift, or hatching from Eggs -- only those captured in battle or obtained via trades. I will most likely update this with support for these methods of obtaining Unown eventually, though.

* Save files from before this was added will not have Unown forms registered even if the player has already captured them, but will register the player if they catch them again.

### Credits

Research made possible by [pokeemerald](https://github.com/pret/pokeemerald) and [pokefirered](https://github.com/pret/pokefirered).

Spherical Ice initially made the [Unown Report code](https://github.com/sphericalice/bpre-unown-report).  I forked it and ported it to the [CFRU's build system](https://github.com/BluRosie/bpre-unown-report) (also here).

Skeli made the [build system used in the CFRU](https://github.com/Skeli789/Complete-Fire-Red-Upgrade) which is used here.
