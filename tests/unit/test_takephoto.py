import pytest
from camocchi import Camocchi
import os


@pytest.mark.one
def test_feat_one(monkeypatch):

    filename = str(os.getcwd() + "/image.png")
    monkeypatch.setenv("OCCHI_PATH_IMAGE", filename, prepend=False)

    camocchi = Camocchi(module="one")
    camocchi.run()

    files = os.listdir(os.getcwd())

    assert "image.png" in files

    os.remove(filename)
