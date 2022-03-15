OCCHI_PATH_IMAGE:=/etc/occhi/source.png

export OCCHI_PATH_IMAGE

clean:
	@find ./ -name '__pycache__' -exec rm -rf {} \;
	@rm -rf .cache
	@rm -rf .pytest_cache
	@rm -rf build
	@rm -rf dist
	@rm -rf *.egg-info

envs: 
	@echo $(OCCHI_PATH_IMAGE)

takephoto:
	python capture_image/test.py

check:
	black capture_image/*.py
	black tests/unit/*.py
	flake8 capture_image/*.py
	flake8 tests/unit/*.py
	mypy tests
	mypy capture_image

flake:
	flake8 capture_image/*.py
	flake8 tests/unit/*.py

black:
	black capture_image/*.py
	black tests/unit/*.py

test:
	pytest
