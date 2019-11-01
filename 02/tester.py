import subprocess

def check(expression,result):
    lstArgs = ["./main"] + expression.split(" ")
    out = subprocess.run(args = lstArgs,stdout=subprocess.PIPE,universal_newlines = False)
    if out.stdout != result:
        print('Error: got {1} instead of {0}'.format(result,out.stdout))
    else:
        print('OK')

#receiving binary strings from process out.stdout
print("Start testing:")

check('100000 20000000 12 --reset 10',b'100000\n!20000000\n99988\n100000\n99990\n')
check('10 9 8 7 6 5 4 1 122 --reset 3 --reset',b'10\n1\n!8\n!7\n!6\n!5\n!4\n0\n!122\n10\n7\n10\n')
check('0 99 1 468 --reset 1',b'0\n!99\n!1\n!468\n0\n!1\n')
check('1 0 1 0 1 0 --reset 1 --reset 1 --reset 1',b'1\n1\n0\n0\n!1\n0\n1\n0\n1\n0\n1\n0\n')
