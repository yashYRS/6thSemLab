__kernel void WordFind(__global char *s,__global int *startInd,__global int *endInd,__global char *word,__global int *wordCount) 
{
	int id = get_global_id(0) ; 
	int start = startInd[id] ; 
	int end = endInd[id] ; 
	int flag = 1;
	int k = 0 ; 
	int i ;  
	for (i = start ; i < end ; i++) {
		if (s[i] != word[k])  {
			flag = 0 ; 
			break ; 
		}
		k++ ; 
	}
	if (flag) {
		wordCount[id] = 1 ;
	}  
	else {  
		wordCount[id] = 0  ;
	} 
}