# coding=gbk
# 生成图并以邻接表格式存储为文件
import networkx as nx
import matplotlib.pyplot as plt

G = nx.path_graph(100)
nx.write_adjlist(G,"test.adjlist")
plt.figure(1)
nx.draw(G)

# 佛罗伦斯家庭图
G1 = nx.florentine_families_graph()
nx.write_adjlist(G1,"test1.adjlist")
plt.figure(2)
nx.draw(G1)
plt.show()