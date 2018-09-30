import networkx as nx
import matplotlib.pyplot as plt
import ast

filename='dg_edges'
f=open(filename,'r')
edges=ast.literal_eval(f.read())
f.close()
G=nx.DiGraph()
G.add_edges_from(edges)
pos=nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos, cmap=plt.get_cmap('jet'), node_color='red', node_size=500)
nx.draw_networkx_labels(G,pos)
nx.draw_networkx_edges(G,pos,edgelist=G.edges(),edge_color='black',arrows=True)
plt.show()
