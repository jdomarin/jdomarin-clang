int branch_count = 5;

void branch(int size) {
	int it;
	forward(size);
	right(360/branch_count);
	forward(size);
	for (it=0;it<2;it++)
		left(360/branch_count);
}
void star(int size) {
	int it;
	for (it=0;it<branch_count;it++)
		branch(size);
}
void run() {
	star(100);
	right(120);
	star(80);
	right(120);
	star(60);
	right(120);
}
