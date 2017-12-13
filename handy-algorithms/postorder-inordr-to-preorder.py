post = [4, 2, 7, 5, 9, 8, 6, 3, 1]
inor = [4, 2, 1, 5, 7, 3, 6, 8, 9]

class Node:
    def __init__(self,v):
        self.v = v
        self.l = None
        self.r = None

def build(post,inor):
    assert len(post)==len(inor)
    if not post:
        return None

    root = Node(post[-1])
    if len(post)==1:
        print(root.v)
        return root

    for i in range(len(inor)): #finding index of root in inorder, in i
        if inor[i] == root.v:
            break

    root.l = build(post[:i],inor[:i]) #both arrays from 0 to index i
    root.r = build(post[i:-1],inor[i+1:]) #post skips last value, which is root
    print(root.v)
    return root

def pre(r):
    if r==None:return

    print(r.v)
    pre(r.l)
    pre(r.r)

r = build(post,inor)
#pre(r)
