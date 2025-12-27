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
graph = nx.DiGraph()
internal_stack = []
print(stack)

pos_setter = {}
colours = {}
while i < mx :
    stackval = stack.pop()
    print(stackval)
    i+=1
    if stackval == '!':
        stackval = internal_stack.pop()
        counter +=1
        graph.add_edge(stackval,counter,label='not')
        colours[counter] = 'red'
        internal_stack.append(counter)
    elif stackval == '^':
        stackval1 = internal_stack.pop()
        stackval2 = internal_stack.pop()
        counter +=1
        colours[counter] = 'green'
        graph.add_edge(stackval1,counter,label='and')
        graph.add_edge(stackval2,counter,label='and')

        internal_stack.append(counter)
    elif stackval == 'v':
        stackval1 = internal_stack.pop()
        stackval2 = internal_stack.pop()
        counter +=1
        colours[counter] = 'orange'
        graph.add_edge(stackval1,counter,label='or')
        graph.add_edge(stackval2,counter,label='or')

        internal_stack.append(counter)
    else:
        colours[stackval] = 'gray'
        pos_setter[stackval] = ord(stackval)-63
        graph.add_node(stackval)
        internal_stack.append(stackval)


import matplotlib.pyplot as plt

member = graph.to_undirected()
pos=nx.bfs_layout(member,counter,align='horizontal')

listcol = []
for node in graph.nodes:
    listcol.append(colours[node])
import math

nx.draw(graph,pos = pos,arrows=True,node_color=listcol,node_size=25)
plt.show()
