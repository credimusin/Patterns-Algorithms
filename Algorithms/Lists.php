<?php

// Custom list


class ListsNode
{
    public ?self $next = null;
    public ?self $prev = null;
    
    public function __construct(
        public mixed $value,
    )
    {}
}

class MyList
{
    private ?ListsNode $head = null;
    private ?ListsNode $tail = null;
    private int $countNode = 0;

    public function push (ListsNode $node): void
    {
        $this->countNode++;
        
        if (!$this->head) {
            $this->head = $node;
        } elseif (!$this->tail) {
            $this->head->next = $node;
            $this->tail = $node;
        } else {
            $this->tail->next = $node;
            $this->tail = $node;
        }
    }

    public function pop (): void
    {
        $current = $this->head;
        while ($current->next !== $this->tail ){
            if ($current === $this->tail) {
                $this->tail = $current;
                $current->next = null;
                break;
            }
            $current = $current->next;
        }
        $this->tail = $current;
    }

    public function shift (): void
    {
        $this->head = $this->head->next;
    }

    public function iter ()
    {
        $current = $this->head;
        while ($current) {
            echo $current->value . PHP_EOL;
            $current = $current->next;
        }
    }

    public function search ($value): ?ListsNode
    {
        $current = $this->head;

        while ($current) {
            if ($current->value === $value) {
                return $current;
            }
            $current = $current->next;
        }
        return null;
    }

    public function count (): int
    {
        return $this->countNode;
    }
}


$list = new MyList();

$list->push(new ListsNode(1));
$list->push(new ListsNode(2));
$list->push(new ListsNode(8));
$list->push(new ListsNode(5));
$list->push(new ListsNode(3));

var_dump($list->search(3));

var_dump($list->count());
