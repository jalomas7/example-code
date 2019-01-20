my %counter;

while (my $line = <> ) {
    chomp $line;
    foreach my $str (split /\s+/, $line) {
        $counter{$str}++;
    }
}

foreach my $word (sort keys %counter) {
    printf "%s : %s\n", $word, $counter{$word};
}
