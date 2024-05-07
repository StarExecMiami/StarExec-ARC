import sys
import os
# idvPath = os.path.dirname(os.path.realpath(__file__))
idvPath = "/home/tptp/ServiceTools/IDVDir"

sys.path.insert(0, idvPath)
from app import app as application

