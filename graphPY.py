import networkx as nx
import matplotlib.pyplot as plt
import ast

filename='dg_edges'
f=open(filename,'r')
lines=f.readlines()
edges=ast.literal_eval(lines[0])
reflex_edges = ast.literal_eval(lines[1])
f.close()
G=nx.DiGraph()
total_edges=edges+reflex_edges
G.add_edges_from(total_edges)
pos=nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos, cmap=plt.get_cmap('jet'), node_color='red', node_size=500)
nx.draw_networkx_labels(G,pos)
nx.draw_networkx_edges(G,pos,edgelist=edges,edge_color='black',arrows=True)
if reflex_edges:
    collection=nx.draw_networkx_edges(G, pos, edgelist=reflex_edges, edge_color='green', arrows=True)
    for patch in collection:
        patch.set_linestyle('dotted')
plt.show()
