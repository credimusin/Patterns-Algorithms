<?php
/**
 * Singleton Pattern
 * Ensures a class has only one instance and provides a global point of access to it.
*/

class SingletonExample
{
    // Set
    private static ?self $instance = null;
    private static string $name;
}
