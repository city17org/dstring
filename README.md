DSTRING(1)

### NAME

**dstring** - return a deterministic string

### SYNOPSIS

**dstring**
\[**-l**&nbsp;*length*]
\[**-n**&nbsp;*number*]

### DESCRIPTION

**dstring**
is a utility that will return a string that includes a lowercase letter, an
uppercase letter, a number and a special character.

When run without any options
**dstring**
will print one string that is 16 characters long to
*stdout*.

The options are as follows:

**-l** *length*

> Return a string that is
> *length*
> characters long.

**-n** *number*

> Return
> *number*
> numbers of strings.

### EXIT STATUS

The **dstring** utility exits&#160;0 on success, and&#160;&gt;0 if an error occurs.

### SEE ALSO

arc4random(3)

### AUTHORS

Sean Davies &lt;[sean@city17.org](mailto:sean@city17.org)&gt;
