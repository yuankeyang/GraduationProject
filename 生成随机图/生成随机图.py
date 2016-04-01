# coding=gbk
# 生成图并以邻接表格式存储为文件
import networkx as nx
import matplotlib.pyplot as plt

G = nx.gnp_random_graph(200, 0.1)
nx.write_adjlist(G,"../test1.adjlist")
plt.figure(1)
nx.draw(G)
plt.show()