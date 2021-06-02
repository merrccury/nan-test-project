{
  "targets": [
    {
      "target_name": "main",
      "sources": [ "main.cpp" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}