# Refactoring

This page describes various refactoring options, available via selection menus and hotkeys:

![refactoring-menu]

### Melodic inversion

The `Alt + I` hotkey applies melodic inversion to selected notes. This contrapuntal derivation is better [described on Wikipedia](https://wikipedia.org/wiki/Inversion_(music)#Melodies); in short, it "flips" the melodic line upside down.

### Retrograde

The `Alt + R` hotkey applies another contrapuntal derivation, [retrograde](https://wikipedia.org/wiki/Retrograde_(music)) or "walking backward".

[Retrograde inversion](https://wikipedia.org/wiki/Retrograde_inversion), which is "backwards and upside down", can be done by combining inversion and retrograde.

**Tip**: use the retrograde hotkey to quickly swap two neighbor chords:

![retrograde-swap-chords]

Or to swap two notes like this:

![retrograde-swap-notes]

The retrograde hotkey also works in the pattern roll, re-ordering all selected clips backwards for each row:

![reverse-clips-order]

### Cleanup overlaps

The `Alt + O` hotkey removes duplicate notes and corrects lengths in a way that notes do not overlap.

## Transposition and inversion

Not listed in the menu, but also handy: the `Shift + Up` and `Shift + Down` hotkeys transpose the selected notes one octave up or down.

Also, `Alt + Shift + Up` and `Alt + Shift + Down` are used for transposition by a "fifth" - a transposition by +7 or -7 semitones in the 12-tone temperament, or by the closest equivalent of a perfect fifth in other temperaments, e.g. +18/-18 for 31-edo, etc.

The latter is useful for introducing short-term chord modulations to a "neighboring key" (one step in either direction on the circle of fifths).

The above hotkeys also work for pattern roll selection: creating track ["instances"](tips-and-tricks.md#clips-and-track-grouping) and modulating them may help prototyping the piece's structure.

### Chord inversion

Use the `Control + Up` and `Control + Down` hotkeys for chord inversion (don't confuse it with [melodic inversion](#melodic-inversion)).

Chord inversion treats selected notes as chord(s); the lowest note in each chord moves one octave up (or the highest note moves one octave down), while all others remain unchanged.

### In-scale transposition

Use the `Alt + Up` and `Alt + Down` hotkeys to transpose the selected notes using in-scale keys only:

![inscale-transposition]

The notes which are out of scale will be aligned up or down to the nearest in-scale keys.

More generally, you can think of it as "transposition using highlighted rows only". For example, when the scales highlighting [flag](tips-and-tricks.md#scales-highlighting) is turned off, it can be useful in microtonal temperaments to transpose notes using only those keys which [approximate](configs.md#temperaments) the 12-tone scale.

#### Align to scale

Similarly to above, the `Alt + A` hotkey will snap the selected notes to the nearest highlighted rows.

### Staccato and legato

The `Alt + S` and `Alt + L` hotkeys apply staccato and legato commands to the selection, respectively. Staccato simply shortens all selected notes (`Alt + Shift + S` shortens them to their shortest length). Legato connects selected notes together in a way that each note lasts until the next note begins:

![staccato-legato]

### Move to track

Pretty self-explanatory shorthand; this function is also available in the [command palette](command-palette.md): press `:` and select another track to move the selected notes to. The "closest" tracks will be listed first for convenience.

## Rescaling

This re-aligns the selected notes or the entire sequence into one of the parallel modes of the same tonic. You can think of it as introducing the in-place [modal interchange](https://wikipedia.org/wiki/Borrowed_chord).

As well as the [chord tool](tips-and-tricks.md#chord-tool), re-scaling assumes that the harmonic context is specified correctly.

*Tip: press the `R` hotkey to apply re-scaling interactively instead of having to choose the target scale from menus.*

Note that this function doesn't change the key signature. Consider using it for introducing brief or transitory variations to bring more harmonic color. If you want to re-scale an entire section of your piece, use the next option:

#### Quick rescale tool

Right-click on any key signature at the timeline to choose another scale into which all tracks will be translated.

This affects all notes in all tracks until the next key signature or the end of the project and updates the key signature. Any out-of-scale notes will be left in their original positions:

![quick-rescale-desktop]

On mobile platforms, long-tap on the key signature:

![quick-rescale-mobile]

## Arpeggiators

Arpeggiators submenu is available in the notes selection menu. If you have created any arpeggiators, you will also find a button on the right sidebar to apply one of them to a selection.

### How arpeggiators work

The idea behind arpeggiators is to remember any custom sequence of notes in their in-scale keys, so that the sequence is no longer dependent on the scale, and later apply that scale-agnostic sequence to some chords in any different harmonic context.

Arpeggiators also rely on time signatures to remember bar starts. When you apply the arpeggiator, it will try to align to your time context by skipping some of its keys to the nearest bar start if necessary when it hits a bar start on the timeline.

### Creating an arpeggiator

Because the creation and use of arpeggiators is tied to harmonic context, arpeggiators rely on valid key signatures at the timeline.

 * First, create any sequence in the current key and scale (enable [scales highlighting](tips-and-tricks.md#scales-highlighting) to avoid confusion). Any out-of-scale keys will be ignored.
 * To create a named arpeggiator from that sequence, select it and press the `Shift + A` hotkey or select a submenu item.
 * After that, in any other place, apply that arpeggiator to any selection, presumably some chords.

### Editing arpeggiators

Helio doesn't provide a separate editor for arpeggiators, but, since each arpeggiator is simply a sequence within a scale, consider the workaround that I ended up using: have a separate project just for arpeggiators and keep them in distinct tracks for convenience, so updating an arpeggiator after editing it is just selecting all events and pressing `Shift + A` to save it under the same name.

To delete an arpeggiator, manually edit your [arpeggiators.json](configs.md#user-configs) in the [documents](index.md#the-projects-directory) directory.


[refactoring-menu]: images/refactoring-menu.png "Selection refactoring menu"
[retrograde-swap-notes]: images/retrograde-swap-notes.png "Swap two neighbor notes with Alt + R hotkey"
[retrograde-swap-chords]: images/retrograde-swap-chords.png "Swap two neighbor chords with Alt + R hotkey"
[reverse-clips-order]: images/reverse-clips-order.png "Retrograde hotkey applied to pattern roll selection"
[inscale-transposition]: images/inscale-transposition.png "In-scale transposition"
[quick-rescale-mobile]: images/quick-rescale-mobile.png "The quick rescale tool on mobile"
[quick-rescale-desktop]: images/quick-rescale-desktop.png "The quick rescale tool on desktop"
[staccato-legato]: images/staccato-legato.png "Staccato and legato shortcuts"
