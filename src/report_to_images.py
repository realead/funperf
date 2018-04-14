import os
import sys

import pandas as pd
import matplotlib.pyplot as plt


input_file=sys.argv[1]
output_folder=os.path.dirname(input_file)

SUFFIX='(x)'

data=pd.read_csv(input_file)


#trig:
def create_image(fun_names, file_name):

    for name in fun_names:
        vals=data.loc[data['fun_name'] == name]
        plt.semilogx(vals.argument, vals.flops, label=name+SUFFIX)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('flops')
    #plt.show()
    plt.savefig(file_name)
    plt.close()



create_image(["sin", "cos", "tan"], os.path.join(output_folder,'trig.png'))
create_image(["asin", "acos", "atan"], os.path.join(output_folder,'atrig.png'))
create_image(["sinh", "cosh", "tanh"], os.path.join(output_folder,'hyp.png'))
create_image(["asinh", "acosh", "atanh"], os.path.join(output_folder,'ahyp.png'))
create_image(["sqrt", "exp", "log"], os.path.join(output_folder,'others.png'))


