# Files
signal.c - c file with a stupid signal handler

# Using

## Compile signal.c

```gcc -pedantic -Werror -Wall signal.c  -o testing ```

## Execute

```./testing```

## Sending a signal from another terminal (running bash)

### Tedious ways

Find the pid of the c program. Execute the following command:

```kill -SIGINT 1243```

assuming that the pid was 1234

### Using bach function

Define a bach function by copy/pasting the following code snippet in your shell:

```sigge() { PID=$(ps auxww | grep testing | grep -v grep | awk '{ print $2 }'); kill -$1 $PID; }```

Then use the function like this:

```sigge SIGINT```

which will send the SIGINT signal to the c program

