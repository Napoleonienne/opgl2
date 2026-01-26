dic ={}
def fibo(n,dic):
    if n in dic:
        return dic[n]
    if n <= 1 :
        dic[n] = 1
    else:    
        dic[n] = fibo(n-1,dic)+fibo(n-2,dic)
    return dic[n]

def fibo2(n):
    u0= u1 = 1
    for i in range(n):
        temp = u1
        u1 = u0 +u1
        u0 =u1
    return u1

print(fibo(100,dic))

class liste_ch():
    def __init__(self,val= None):
        self.valeur =val
        self._suivant = None
        self.n = 0
    
    def suivan(self):
        return self.suivant()

    def ajouter(self,val):
        if self.valeur == None:
            self.valeur = val
        else:
            if self._suivant == None:
                self._suivant = liste_ch(val)

            else:
                self._suivant.ajouter(val)
    
    def trouver(self,val):
        if self.valeur == val:
            return True
        else:
            if self._suivant != None:
                self._suivant.trouver(val)
            else:
                return False 
            
    def pos(self,val,n=0):
        """
        Docstring for pos
        
        :param val: valeur a chercher
        :param n: pas toucher n
        """
        if self.valeur ==None:
            return -1
        if self.valeur == val:
            return n
        else:
            if self._suivant:
                self._suivant.pos(val,n= n+1)

        


    def __len__(self,n):
        if self.valeur ==None:
            pass
        
        

        return 