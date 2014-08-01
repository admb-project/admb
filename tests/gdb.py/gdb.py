import sys
import gdb
gdb.execute("file ./simple")
gdb.execute("break main")
gdb.breakpoints()
gdb.execute("run")
gdb.execute("bt")

class HelloWorld:

  def __init__ (self):
    self.name = "HelloWorld"
    print "Hello, World!"

HelloWorld ()

gdb.execute("continue")
