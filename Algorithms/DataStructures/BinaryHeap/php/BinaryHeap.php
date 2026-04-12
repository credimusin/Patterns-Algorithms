<?php
/**
 * BinaryHeap Algorithm
 *
*/


class Scrap
{
    public int $value;

    public function __construct(int $value)
    {
        $this->value = $value;
    }
}

class Heap
{
    private array $heap = [];

    public function push(Scrap $node):void
    {
        $this->heap[] = $node;

        $n = count($this->heap) - 1;

        if ($n === 0) {
            return;
        }

        while ($n > 0) {
            $head = (int) floor(($n - 1) / 2);
            if ($this->heap[$n]->value > $this->heap[$head]->value) {
                $temp = $this->heap[$head];
                $this->heap[$head] = $this->heap[$n];
                $this->heap[$n] = $temp;
                $n = $head;
            } else {
                return;
            }
        }
    }

    public function pop(Scrap $node): void
    {
        return;
    }

    public function search(Scrap $node): Scrap
    {
        return $node;
    }
}

$list = new Heap();

$list->push(new Scrap(1));
$list->push(new Scrap(2));
$list->push(new Scrap(8));
$list->push(new Scrap(5));
$list->push(new Scrap(3));
$list->push(new Scrap(11));
$list->push(new Scrap(1));
$list->push(new Scrap(12));
$list->push(new Scrap(4));

var_dump($list);
