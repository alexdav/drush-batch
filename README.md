# How to run the script
- `cd /path/to/script`
- `composer install --no-plugins --no-scripts`
- `drush --root=/var/www/html scr script.inc`

# How to add utilize the script
- Load your array of entities inside the `$entities` array inside [entities.inc](entities.inc)
  - Follow the syntax as described in the file.
- Update the `do_work()` function inside [work.inc](work.inc)

