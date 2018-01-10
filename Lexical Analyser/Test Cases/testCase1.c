int main()
{
	// single line comment
	
	/* block
	comment */

	int a,b,_z;
	float c;

	a=2;
	b=10;
	c=5.3e-3;

	if(a!=2)
	{
		a++;
	}
	else if(b!=10)
	{
		b-=3;
	}
	else
	{
		(a==b)?a--:b*=2;
	}

	/* this is 
	a /* multi-line
	comment */
}