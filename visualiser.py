#!/usr/bin/env python3

stack = []

with open('test.txt','r') as w:
    line = w.readline()
    for char in line:
        stack.append(char)


mx = len(stack)
i=0

counter = 0;
import networkx as nx
graph = nx.Graph()
internal_stack = []
print(stack)

pos_setter = {}
while i < mx :
    stackval = stack.pop()
    print(stackval)
    i+=1
    if stackval == '!':
        stackval = internal_stack.pop()
        counter +=1
        graph.add_edge(stackval,counter,label='not')
        internal_stack.append(counter)
    elif stackval == '^':
        stackval1 = internal_stack.pop()
        stackval2 = internal_stack.pop()
        counter +=1
        graph.add_edge(stackval1,counter,label='and')
        graph.add_edge(stackval2,counter,label='and')
        internal_stack.append(counter)
    elif stackval == 'v':
        stackval1 = internal_stack.pop()
        stackval2 = internal_stack.pop()
        counter +=1
        graph.add_edge(stackval1,counter,label='or')
        graph.add_edge(stackval2,counter,label='or')
        internal_stack.append(counter)
    else:
        pos_setter[stackval] = ord(stackval)-63
        graph.add_node(stackval)
        internal_stack.append(stackval)


import matplotlib.pyplot as plt


pos=nx.bfs_layout(graph,counter,align='horizontal')

import math
for i in pos_setter:
    pos[i] = ((pos_setter[i] - len(pos_setter)/2)/4, math.log(counter/len(pos_setter))/4)
nx.draw(graph,pos = pos,with_labels=True)
plt.show()
