#����ͼ�����ڽӱ��ʽ�洢Ϊ�ļ�
import networkx as nx
import matplotlib.pyplot as plt

G = nx.path_graph(100)
nx.write_adjlist(G,"test.adjlist")
nx.draw(G)
plt.show()