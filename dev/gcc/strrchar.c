int main(int argc , char *argv[])
{
	char *program;
	char path[]="/pathc/to/bass1_export";
	program = strrchr(path,'/');
	printf(program);	
	printf("\n");	
	if ( program ) program++;
	else program = path;
	printf(program);	
	printf("\n");	
	return 0;
	
}
