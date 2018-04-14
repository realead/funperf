import os
import sys

import pandas as pd
import matplotlib.pyplot as plt


input_file=sys.argv[1]
output_folder=os.path.dirname(input_file)

SUFFIX='(x)'

data=pd.read_csv(input_file)
for name in data.fun_name.unique():
    vals=data.loc[data['fun_name'] == name]
    plt.semilogx(vals.argument, vals.flops, label=name+SUFFIX)
plt.legend()
plt.xlabel('x')
plt.ylabel('flops')
#plt.show()
plt.savefig(os.path.join(output_folder,'trig.png'))


