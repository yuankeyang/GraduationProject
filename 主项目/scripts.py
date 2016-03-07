#生成图并以邻接表格式存储为文件
import networkx as nx
import matplotlib.pyplot as plt

G = nx.path_graph(100)
nx.write_adjlist(G,"test.adjlist")
nx.draw(G)
plt.show()