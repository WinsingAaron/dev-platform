import os
import sys

ROOT = os.path.dirname(os.path.abspath(os.path.dirname(__file__)))
# example/swig/helloworld
HELLO_PATH = os.path.join(ROOT, "examples", "swig", "helloworld")

sys.path.append(HELLO_PATH)

import hello

hello.hello_print()
