# Turing Machine Simulator

This is a small Turing machine simulator that I programmed to check one of my exercises on the topic.

## What is a Turing Machine?

From Wikipedia:
> A Turing machine is a mathematical model of computation that defines an abstract machine that manipulates symbols on a strip of tape according to a table of rules. Despite the model's simplicity, given any computer algorithm, a Turing machine capable of implementing that algorithm's logic can be constructed.

Read more about this [here](https://en.wikipedia.org/wiki/Turing_machine).

## What was the exercise about?

The exercise asked me to create a Turing machine that checked whether a given string, made from the alphabet composed of the characters *a*, *b* and *c*, contained the same number of *a*'s and *b*'s or the same number of *a*'s and *c*'s.

While the authors solved the exercise through a 4-tape Turing machine, I found that a 3-tape Turing machine would be more efficient, and went ahead and solved it through that kind of machine.

To test my solution, I decided to make this program in C.

## How does the emulation work?

A Turing machine is essentially composed of infinite tapes (in this case, four), and a [Finite-State Automaton](https://en.wikipedia.org/wiki/Finite-state_machine) as the *processing component* of the machine.

I recreated the four tapes, one being the input tape and the other three the memory tapes, through character arrays. For memory usage, I decided to make the tapes 100 character long at most, but there technically is no limit to the length of the tape.

Then I programmed the logic of the FSA with if-else statements and a switch statement: the machine reads the input tape one character at a time and writes one *A* in the first tape for each *a* in the input tape, one *B* in the second tape for each *b* and one *C* in the third tape for each *c*.

Once the input string ends (which is when the machine reads blank space, in this case represented by the null character `\0`), the machine stops and reverses the three memory tapes, deleting one symbol from each, until at least one of the tapes returns to the beginning, which is marked by a special symbol: *Z*.

If all three of the tapes or if the *A* tape and one of the other two tapes return to *Z* at the same time, then the string meets the criteria imposed by the exercise, and the machine accepts it.

The program uses a `struct` to represent the machine's configuration, which includes the tapes' indexes, the state in which the machine currently is (in my original design, the machine has three states: `q0`, `q1` and `q2`) and whether it will accept the input string or not.

## How do I watch the machine do its work step by step?

To do that, I used the debugger in VS Code and put breakpoints in the main loops of the program. Just watch the four tapes get updated through the *Variables* window.

I might update this program in the future adding a visualiser for the tapes.
