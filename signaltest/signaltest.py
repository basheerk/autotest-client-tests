import os

from autotest.client import test
from autotest.client.shared import utils


class signaltest(test.test):
    version = 1
    preserve_srcdir = True

    def initialize(self):
        self.job.require_gcc()

    # git://git.kernel.org/pub/scm/linux/kernel/git/tglx/rt-tests.git
    def setup(self):
        os.chdir(self.srcdir)
        utils.make()

    def execute(self, args='-t 10 -l 100000'):
        utils.system(self.srcdir + '/signaltest ' + args)
