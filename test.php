<?php

call_user_func_array(function($data) {
    print_r($data);
}, [[1, 2, 3]]);