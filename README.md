# Fault Injection Simulator

A simple framework to simulate fault attacks on x86 binaries.

## Usage

The simulator loads a statically-compiled x86 ELF binary and a "fault" script. The fault script contains commands for the simulator to induce certain kinds of faults (see Fault Script). The simulator simply runs the binary, and induces the faults as specified in the fault script.

The behavior of the simulator can be configured directly via the victim binaries. A victim binary can contain configuration options for the simulator (see Configuration).
For example, to run a demo victim:

    ./simulator demos/victim1.fault demos/victim1


## Fault Script

Faults are induced using fault scripts which are loaded with the binary. Commands typically modify parts of the memory, which can be data or code, when they are triggered.
Lines starting with # are ignored and can be used for comments.

### Trigger
Currently, a trigger can be an absolute RIP value (i.e., when the instruction pointer reaches a certain position in the binary) or the n-th executed instruction.

#### Absolute RIP

    @<RIP>

Triggers a fault when the RIP reaches a certain position in the executable. The RIP can be specified as decimal or hexadecimal value.

##### Example
Skip two bytes when the instruction pointer is at 0x400b51: `skip 2 @0x400b51`

#### Instruction Count

    #<Instruction Number>

Triggers a fault after that many instructions were executed.

##### Example
Skip two bytes in the instruction stream after executing 10000 instructions: `skip 2 #10000`

### Commands
The following commands are supported:

#### skip

    skip <bytes> <trigger>

Skips the given number of bytes <bytes> in the instruction stream when the given trigger <trigger> is reached. This can also be negative to jump backwards. Note that this does not skip <bytes> instructions, as many instructions are larger than one byte.

##### Example
Skip 1 byte when the instruction pointer is at 0x400b51: `skip 1 @0x400b51`

#### zero

    zero <address> <trigger>

Sets the given memory address <address> to 0 when the given trigger <trigger> is reached. The function zeroes out one byte (i.e., 8 bit).

##### Example
Write a zero word to address 0x6bb330 if the instruction pointer reaches 0x400b6e: `zero 0x6bb330 @0x400b6e`

#### havoc

    havoc <address> <trigger>

Sets the given memory address <address> to a random value when the given trigger <trigger> is reached. The function affects one byte (i.e., 8 bit).

##### Example
Write a random word to address 0x6bb330 if the instruction pointer reaches 0x400b6e: `havoc 0x6bb330 @0x400b6e`


#### bitflip

    bitflip <bit index> <destination> <trigger>

Flips the <bit index>-th bit at the memory address <destination> when the given trigger <trigger> is reached.

##### Example
Flips bit 0 at the memory location 0x400b59 if the instruction pointer reaches 0x400b4d: `bitflip 0 0x400b59 @0x400b4d`

#### log

    log <log type>

Enables log output for certain events. Supported events are `rip` (prints the current instruction pointer for every instruction), `inscnt` (prints the current instruction counter for every instruction), and `fault` (prints the details of every successfully induced fault).

## Configuration

The simulator can be configured via the loaded binaries. A binary can include configurations which blacklist certain functions and modify other behavior of the simulator.
To include a configuration, simply include the `faultconfig.h` header and insert as many `FAULT_CONFIG` statements as required.

An example binary with embedded configuration can look like this:

    #include <stdio.h>
    #include <faultconfig.h>

    volatile int is_admin = 0;

    int main() {
        if(!is_admin) {
            puts("Nope, you are not admin\n");
            return 1;
        } else {
            puts("Success!\n");
            return 0;
        }

    }

    FAULT_CONFIG("NOHAVOC");
    FAULT_CONFIG("NOSKIP");
    FAULT_CONFIG("TIMEOUT=3");
    FAULT_CONFIG("FAILEVERY=2");
    FAULT_CONFIG("COOLDOWN=100");

The following configuration options are supported:

### Feature Blacklist

Any of the supported commands for fault scripts can be disabled for a binary. Blacklisting a feature is done with the options `NOSKIP`, `NOHAVOC`, `NOZERO`, `NOBITFLIP`, `NOLOG`.

### Parameter Blacklist

For the `log` command it is also possible to blacklist only certain log types: `NOLOGFAULT`, `NOLOGRIP`, `NOLOGINSTRUCTION`.
It is also possible to blacklist triggers: `NORIPTRIGGER`, `NOINSTRUCTIONTRIGGER`.

### Parameter Ranges

For the `skip` command it is possible to restrict the range of skippable bytes. The default is [-15,15], but it can be configured with `MINSKIP=<skip>` and `MAXSKIP=<skip>`, e.g. `FAULT_CONFIG("MINSKIP=0"); FAULT_CONFIG("MAXSKIP=2");` to only allow skipping 1 or 2 bytes.

### Reliability

It is possible to define a probability with with a fault will not be induced. `FAILEVERY=<faults>` defines that on average 1 out of <faults> faults fails. For example, with `FAULT_CONFIG("FAILEVERY=2");`, 50% of all faults are not induced. By default, all faults are successful.
Additionally, `COOLDOWN=<instruction>` defines that after inducing a fault, it takes <instruction> instructions until another fault can be induced. By default, there is no cooldown.

## Miscellaneous

A binary can define a timeout in seconds after which it is terminated: `TIMEOUT=<seconds>`. If the binary runs into the timeout, the exploit is considered to be unsuccessful. The default timeout is 30 seconds.
To ensure reproducibility, the seed for the random function (used e.g. in `havoc`) can be fixed with `SEED=<seed>`. The default seed is `time(NULL)`.
